#include "HashMap.hpp"

namespace {
    static const unsigned int FNV_PRIME_32 = 16777619u;
    static const unsigned int FNV_OFFSET_BASIS_32 = 2166136261u;

    unsigned int fnv_a1(const std::string& str) {
        unsigned int hash = FNV_OFFSET_BASIS_32;
        for(const char& c: str) {
            hash ^= (unsigned int)c;
            hash *= FNV_PRIME_32;
        }
        return hash;

    }
}

HashMap::HashMap()
{
    hasher = fnv_a1;
    bucket_size = initialBucketCount;
    bucket = new Node*[initialBucketCount];
    init_bucket();
}

HashMap::HashMap(HashFunction hasher)
{
    this->hasher = hasher;
    bucket_size = initialBucketCount;
    bucket = new Node*[initialBucketCount];
    init_bucket();
}

HashMap::HashMap(const HashMap& hm)
{
    hasher = hm.hasher;
    bucket_size = hm.bucketCount();
    bucket = new Node*[bucket_size];
    init_bucket();
    for (unsigned int i = 0; i < bucket_size; i++) {
        Node *srcNode = hm.bucket[i];
        while (srcNode) {
            Node *destNode = bucket[i];
            bucket[i] = new Node{srcNode->key, srcNode->value, destNode};
            srcNode = srcNode->next;
        }
    }
}

HashMap::~HashMap()
{
    free_bucket();
}

HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != &hm) {
        Node **old_bucket = bucket;
        size_t old_bucket_size = bucket_size;
        bucket_size = hm.bucket_size;
        bucket = new Node*[bucket_size];
        init_bucket();
        for (unsigned int i = 0; i < bucket_size; i++) {
            Node *node = hm.bucket[i];
            while (node) {
                add(node->key, node->value);
                node = node->next;
            }
        }
        free_bucket(old_bucket, old_bucket_size);
    }
    return *this;
}

void HashMap::add(const std::string &key, const std::string &value)
{
    unsigned int hash = hasher(key) % bucket_size;
    Node *head = bucket[hash];
    Node *node = head;
    while (node) {
        if (node->key == key) {
            return;
        }
        node = node->next;
    }
    bucket[hash] = new Node{key, value, head};

    if (loadFactor()>.8) {
        Node **old_bucket = bucket;
        size_t old_bucket_size = bucket_size;
        bucket_size = bucket_size * 2 + 1;
        bucket = new Node*[bucket_size];
        init_bucket();
        for (unsigned int i = 0; i < old_bucket_size; i++) {
            Node *node = old_bucket[i];
            while (node) {
                add(node->key, node->value);
                node = node->next;
            }
        }
        free_bucket(old_bucket, old_bucket_size);
    }
}

void HashMap::remove(const std::string& key)
{
    unsigned int hash = hasher(key) % bucket_size;
    Node *node = bucket[hash];
    Node *prev = nullptr;
    while (node) {
        if (node->key == key) {
            if (prev) {
                prev->next = node->next;
                delete node;
            } else {
                delete node;
                bucket[hash] = nullptr;
            }
            break;
        }
        prev = node;
        node = node->next;
    }
}

bool HashMap::contains(const std::string& key) const
{
    unsigned int hash = hasher(key) % bucket_size;
    Node *node = bucket[hash];
    while (node) {
        if (node->key == key) {
            return true;
        }
        node = node->next;
    }
    return false;
}

std::string HashMap::value(const std::string& key) const
{
    unsigned int hash = hasher(key) % bucket_size;
    Node *node = bucket[hash];
    while (node) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return "";
}

unsigned int HashMap::size() const
{
    unsigned int pair_count = 0;
    for (unsigned int i = 0; i < bucket_size; i++) {
        Node *node = bucket[i];
        while (node) {
            pair_count++;
            node = node->next;
        }
    }
    return pair_count;
}

unsigned int HashMap::bucketCount() const
{
    return bucket_size;
}

double HashMap::loadFactor() const
{
    return size() / (double)bucket_size;
}

unsigned int HashMap::maxBucketSize() const
{
    unsigned int max_bucket_size = 0;
    unsigned int pair_count;
    for (unsigned int i = 0; i < bucket_size; i++) {
        pair_count = 0;
        Node *node = bucket[i];
        while (node) {
            pair_count++;
            node = node->next;
        }
        if (pair_count > max_bucket_size) {
            max_bucket_size = pair_count;
        }
    }
    return max_bucket_size;
}

void HashMap::free_bucket(Node **bucket, size_t bucket_size)
{
    for (unsigned int i = 0; i < bucket_size; i++) {
        Node *node = bucket[i];
        while (node) {
            Node *next = node->next;
            delete node;
            node = next;
        }
    }
    delete [] bucket;
}

void HashMap::free_bucket()
{
    free_bucket(bucket, bucket_size);
}

void HashMap::init_bucket()
{
    for (unsigned int i = 0; i < bucket_size; i++) {
        bucket[i] = nullptr;
    }
}
