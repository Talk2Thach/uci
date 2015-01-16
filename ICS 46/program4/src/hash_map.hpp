//Tianya Chen UID=756681
//Edward Xia  UID=149235
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming
#ifndef HASH_MAP_HPP_
#define HASH_MAP_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "array_queue.hpp"   //For traversal


namespace ics {
    
    template<class KEY,class T> class HashMap : public Map<KEY,T>	{
    public:
        typedef ics::pair<KEY,T> Entry;
        HashMap() = delete;
        HashMap(int (*ahash)(const KEY& k), double the_load_factor = 1.0);
        HashMap(int initial_bins, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
        HashMap(const HashMap<KEY,T>& to_copy);
        HashMap(std::initializer_list<Entry> il, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
        HashMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
        virtual ~HashMap();
        
        virtual bool empty      () const;
        virtual int  size       () const;
        virtual bool has_key    (const KEY& key) const;
        virtual bool has_value  (const T& value) const;
        virtual std::string str () const;
        
        virtual T    put   (const KEY& key, const T& value);
        virtual T    erase (const KEY& key);
        virtual void clear ();
        
        virtual int put   (ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop);
        
        virtual T&       operator [] (const KEY&);
        virtual const T& operator [] (const KEY&) const;
        virtual HashMap<KEY,T>& operator = (const HashMap<KEY,T>& rhs);
        virtual bool operator == (const Map<KEY,T>& rhs) const;
        virtual bool operator != (const Map<KEY,T>& rhs) const;
        
        template<class KEY2,class T2>
        friend std::ostream& operator << (std::ostream& outs, const HashMap<KEY2,T2>& m);
        
        virtual ics::Iterator<Entry>& ibegin () const;
        virtual ics::Iterator<Entry>& iend   () const;
        
    private:
        class LN;
        
    public:
        class Iterator : public ics::Iterator<Entry> {
        public:
            //KLUDGE should be callable only in begin/end
            Iterator(HashMap<KEY,T>* iterate_over, bool begin);
            Iterator(const Iterator& i);
            virtual ~Iterator();
            virtual Entry       erase();
            virtual std::string str  () const;
            virtual const ics::Iterator<Entry>& operator ++ ();
            virtual const ics::Iterator<Entry>& operator ++ (int);
            virtual bool operator == (const ics::Iterator<Entry>& rhs) const;
            virtual bool operator != (const ics::Iterator<Entry>& rhs) const;
            virtual Entry& operator *  () const;
            virtual Entry* operator -> () const;
        private:
            ics::pair<int,LN*> current; //Bin Index/Cursor; stop: LN* == nullptr
            HashMap<KEY,T>*    ref_map;
            int                expected_mod_count;
            bool               can_erase = true;
            void advance_cursors();
        };
        
        virtual Iterator begin () const;
        virtual Iterator end   () const;
        //KLUDGE: define
        //virtual ics::Iterator<KEY>&  begin_key   () const;
        //virtual ics::Iterator<KEY>&  end_key     () const;
        //virtual ics::Iterator<T>&    begin_value () const;
        //virtual ics::Iterator<T>&    end_value   () const;
        
    private:
        class LN {
        public:
            LN ()                         : next(nullptr){}
            LN (const LN& ln)             : value(ln.value), next(ln.next){}
            LN (Entry v, LN* n = nullptr) : value(v), next(n){}
            
            Entry value;
            LN*   next;
        };
        
        LN** map      = nullptr;
        int (*hash)(const KEY& k);
        double load_factor;//used/bins <= load_factor
        int bins      = 1; //# bins available in the array
        int used      = 0; //# of key->value pairs in the hash table
        int mod_count = 0; //For sensing concurrent modification
        int   hash_compress (const KEY& key) const;
        void  ensure_load_factor(int new_used);
        LN*   find_key (int bin, const KEY& key) const;
        bool  find_value (const T& value) const;
        LN*   copy_list(LN*   l) const;
        LN**  copy_hash_table(LN** ht, int bins) const;
        void  delete_hash_table(LN**& ht, int bins);
    };
    
    
    
    
    
    template<class KEY,class T>
    HashMap<KEY,T>::HashMap(int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
        map = new LN*[bins];
        for (int i = 0; i < bins; ++i) {
            map[i] = new LN();
        }
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>::HashMap(int initial_bins, int (*ahash)(const KEY& k), double the_load_factor) : bins(initial_bins), hash(ahash),
    load_factor(the_load_factor) {
        if (initial_bins <= 0) {
            throw IcsError("initial_bins must be greater than 0");
        }
        map = new LN*[bins];
        for (int i = 0; i < bins; ++i) {
            map[i] = new LN();
        }
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>::HashMap(const HashMap<KEY,T>& to_copy) : hash(to_copy.hash), load_factor(to_copy.load_factor), bins(to_copy.bins), used(to_copy.used) {
        map = copy_hash_table(to_copy.map, bins);
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>::HashMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop, int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
        map = new LN*[bins];
        for (int i = 0; i < bins; ++i) {
            map[i] = new LN();
        }
        put(start,stop);
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>::HashMap(std::initializer_list<Entry> il,int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
        map = new LN*[bins];
        for (int i = 0; i < bins; ++i) {
            map[i] = new LN();
        }
        for (Entry m_entry : il)
            put(m_entry.first,m_entry.second);
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>::~HashMap() {
        delete_hash_table(map, bins);
    }
    
    
    template<class KEY,class T>
    inline bool HashMap<KEY,T>::empty() const {
        return used == 0;
    }
    
    template<class KEY,class T>
    int HashMap<KEY,T>::size() const {
        return used;
    }
    
    template<class KEY,class T>
    bool HashMap<KEY,T>::has_key (const KEY& key) const {
        return find_key(hash_compress(key), key) != nullptr;
    }
    
    template<class KEY,class T>
    bool HashMap<KEY,T>::has_value (const T& value) const {
        return find_value(value);
    }
    
    template<class KEY,class T>
    std::string HashMap<KEY,T>::str() const {
        std::ostringstream answer;
        answer << *this << "(used=" << used << ",mod_count=" << mod_count << ")";
        return answer.str();
    }
    
    template<class KEY,class T>
    T HashMap<KEY,T>::put(const KEY& key, const T& value) {
        ++mod_count;
        LN *node = find_key(hash_compress(key), key);
        if (node != nullptr) {
            T to_return = node->value.second;
            node->value.second = value;
            return to_return;
        }
        ensure_load_factor(++used);
        int i = hash_compress(key);
        map[i] = new LN({key,value}, map[i]);
        return value;
    }
    
    template<class KEY,class T>
    T HashMap<KEY,T>::erase(const KEY& key) {
        LN *node = find_key(hash_compress(key), key);
        if (node != nullptr) {
            T to_return = node->value.second;
            LN *next = node->next;
            *node = *next;
            delete next;
            --used;
            ++mod_count;
            return to_return;
        }
        std::ostringstream answer;
        answer << "HashMap::erase: key(" << key << ") not in Map";
        throw KeyError(answer.str());
    }
    
    template<class KEY,class T>
    void HashMap<KEY,T>::clear() {
        LN **table = new LN*[bins];
        for (int i = 0; i < bins; ++i) {
            table[i] = new LN();
        }
        delete_hash_table(map, bins);
        map = table;
        ++mod_count;
        used = 0;
    }
    
    template<class KEY,class T>
    int HashMap<KEY,T>::put (ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop) {
        int count = 0;
        for (; start != stop; ++start) {
            ++count;
            put(start->first,start->second);
        }
        return count;
    }
    
    template<class KEY,class T>
    T& HashMap<KEY,T>::operator [] (const KEY& key) {
        LN *node = find_key(hash_compress(key), key);
        if (node != nullptr) {
            return node->value.second;
        }
        put(key, T());
        return find_key(hash_compress(key), key)->value.second;
    }
    
    template<class KEY,class T>
    const T& HashMap<KEY,T>::operator [] (const KEY& key) const {
        LN *node = find_key(hash_compress(key), key);
        if (node != nullptr) {
            return node->value.second;
        }
        std::ostringstream answer;
        answer << "HashMap::operator []: key(" << key << ") not in Map";
        throw KeyError(answer.str());
    }
    
    template<class KEY,class T>
    bool HashMap<KEY,T>::operator == (const Map<KEY,T>& rhs) const {
        if (this == &rhs)
            return true;
        if (used != rhs.size())
            return false;
        for (auto &iter = ibegin(); iter != iend(); ++iter) {
            if (!rhs.has_key(iter->first) || !(iter->second == rhs[iter->first])) {
                return false;
            }
        }
        return true;
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>& HashMap<KEY,T>::operator = (const HashMap<KEY,T>& rhs) {
        if (this == &rhs)
            return *this;
        delete_hash_table(map, bins);
        map = copy_hash_table(rhs.map, rhs.bins);
        bins = rhs.bins;
        used = rhs.used;
        ++mod_count;
        return *this;
    }
    
    template<class KEY,class T>
    bool HashMap<KEY,T>::operator != (const Map<KEY,T>& rhs) const {
        return !(*this == rhs);
    }
    
    
    template<class KEY,class T>
    std::ostream& operator << (std::ostream& outs, const HashMap<KEY,T>& m) {
        outs << "map[";
        
        if (!m.empty()) {
            auto &iter = m.ibegin();
            outs << iter->first << "->" << iter->second;
            for (++iter; iter != m.iend(); ++iter) {
                outs << "," << iter->first << "->" << iter->second;
            }
        }
        
        outs << "]";
        return outs;
    }
    
    //KLUDGE: memory-leak
    template<class KEY,class T>
    auto HashMap<KEY,T>::ibegin () const -> ics::Iterator<Entry>& {
        return *(new Iterator(const_cast<HashMap<KEY,T>*>(this),true));
    }
    
    //KLUDGE: memory-leak
    template<class KEY,class T>
    auto HashMap<KEY,T>::iend () const -> ics::Iterator<Entry>& {
        return *(new Iterator(const_cast<HashMap<KEY,T>*>(this),false));
    }
    
    template<class KEY,class T>
    auto HashMap<KEY,T>::begin () const -> HashMap<KEY,T>::Iterator {
        return Iterator(const_cast<HashMap<KEY,T>*>(this),true);
    }
    
    template<class KEY,class T>
    auto HashMap<KEY,T>::end () const -> HashMap<KEY,T>::Iterator {
        return Iterator(const_cast<HashMap<KEY,T>*>(this),false);
    }
    
    template<class KEY,class T>
    int HashMap<KEY,T>::hash_compress (const KEY& key) const {
        return abs(hash(key)) % bins;
    }
    
    template<class KEY,class T>
    void HashMap<KEY,T>::ensure_load_factor(int new_used) {
        if (new_used / (double)bins > load_factor) {
            int old_bins = bins;
            bins *= 2;
            LN **table = new LN*[bins];
            for (int i = 0; i < bins; ++i) {
                table[i] = new LN();
            }
            for (int i = 0; i < old_bins; ++i) {
                for (LN *node = map[i]; node->next != nullptr; node = node->next) {
                    int j = hash_compress(node->value.first);
                    table[j] = new LN(node->value, table[j]);
                }
            }
            delete_hash_table(map, old_bins);
            map = table;
        }
    }
    
    template<class KEY,class T>
    typename HashMap<KEY,T>::LN* HashMap<KEY,T>::find_key (int bin, const KEY& key) const {
        LN *node = map[bin];
        for (; node->next != nullptr; node = node->next) {
            if (node->value.first == key) {
                return node;
            }
        }
        return nullptr;
    }
    
    template<class KEY,class T>
    bool HashMap<KEY,T>::find_value (const T& value) const {
        for (int i = 0; i < bins; ++i) {
            LN *node = map[i];
            if (node->next != nullptr) {
                for (; node->next->next != nullptr; node = node->next) {
                    if (node->value.second == value) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    template<class KEY,class T>
    typename HashMap<KEY,T>::LN* HashMap<KEY,T>::copy_list (LN* l) const {
        LN *node = new LN();
        for (; l->next != nullptr; l = l->next) {
            node = new LN(l->value, node);
        }
        return node;
    }
    
    template<class KEY,class T>
    typename HashMap<KEY,T>::LN** HashMap<KEY,T>::copy_hash_table (LN** ht, int bins) const {
        LN **table = new LN*[bins];
        for (int i = 0; i < bins; ++i) {
            table[i] = copy_list(ht[i]);
        }
        return table;
    }
    
    template<class KEY,class T>
    void HashMap<KEY,T>::delete_hash_table (LN**& ht, int bins) {
        for (int i = 0; i < bins; ++i) {
            LN *node = ht[i];
            while (node != nullptr) {
                LN *to_delete = node;
                node = node->next;
                delete to_delete;
            }
        }
        delete [] ht;
    }
    
    
    template<class KEY,class T>
    void HashMap<KEY,T>::Iterator::advance_cursors() {
        if (current.first >= 0) {
            if (current.second->next != nullptr && current.second->next->next != nullptr) {
                current.second = current.second->next;
            } else {
                while ((current.second->next == nullptr || current.second->next->next == nullptr)) {
                    ++current.first;
                    if (current.first == ref_map->bins) {
                        current = {-1, nullptr};
                        return;
                    } else {
                        current.second = ref_map->map[current.first];
                        if (current.second->next != nullptr) {
                            return;
                        }
                    }
                }
            }
        }
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>::Iterator::Iterator(HashMap<KEY,T>* iterate_over, bool begin) : ref_map(iterate_over), expected_mod_count(iterate_over->mod_count) {
        if (ref_map->used == 0 || !begin) {
            current = {-1, nullptr};
        } else {
            current = {0, ref_map->map[0]};
            if (current.second->next == nullptr) {
                advance_cursors();
            }
        }
    }
    
    template<class KEY,class T>
    HashMap<KEY,T>::Iterator::Iterator(const Iterator& i) :
    current(i.current), ref_map(i.ref_map), expected_mod_count(i.expected_mod_count), can_erase(i.can_erase) {}
    
    template<class KEY,class T>
    HashMap<KEY,T>::Iterator::~Iterator()
    {}
    
    template<class KEY,class T>
    auto HashMap<KEY,T>::Iterator::erase() -> Entry {
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("HashMap::Iterator::erase");
        if (!can_erase)
            throw CannotEraseError("HashMap::Iterator::erase Iterator cursor already erased");
        if (current.second == nullptr)
            throw CannotEraseError("HashMap::Iterator::erase Iterator cursor beyond data structure");
        
        can_erase = false;
        Entry to_return = current.second->value;
        LN *next = current.second->next;
        *(current.second) = *next;
        delete next;
        --ref_map->used;

        if (current.second->next == nullptr) {
            advance_cursors();
        }
        return to_return;
    }
    
    template<class KEY,class T>
    std::string HashMap<KEY,T>::Iterator::str() const {
        std::ostringstream answer;
        answer << ref_map->str() << "(current=" << current.first << "/" << current.second << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
        return answer.str();
    }
    
    //KLUDGE: cannot use Entry
    template<class KEY,class T>
    auto  HashMap<KEY,T>::Iterator::operator ++ () -> const ics::Iterator<ics::pair<KEY,T>>& {
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("HashMap::Iterator::operator ++");
            
        if (current.first < 0)
            return *this;
        
        if (!can_erase)
            can_erase = true;
        else
            advance_cursors();
        
        return *this;
    }
    
    //KLUDGE: creates garbage! (can return local value!)
    template<class KEY,class T>
    auto HashMap<KEY,T>::Iterator::operator ++ (int) -> const ics::Iterator<ics::pair<KEY,T>>&{
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("HashMap::Iterator::operator ++(int)");
            
        if (current.first < 0)
            return *this;
        
        Iterator* to_return = new Iterator(*this);
        if (!can_erase) {
            can_erase = true;
        } else {
            advance_cursors();
        }
        
        return *to_return;
    }
    
    template<class KEY,class T>
    bool HashMap<KEY,T>::Iterator::operator == (const ics::Iterator<Entry>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("HashMap::Iterator::operator ==");
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("HashMap::Iterator::operator ==");
        if (ref_map != rhsASI->ref_map)
            throw ComparingDifferentIteratorsError("HashMap::Iterator::operator ==");
        
        return current == rhsASI->current;
    }
    
    
    template<class KEY,class T>
    bool HashMap<KEY,T>::Iterator::operator != (const ics::Iterator<Entry>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("HashMap::Iterator::operator !=");
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("HashMap::Iterator::operator !=");
        if (ref_map != rhsASI->ref_map)
            throw ComparingDifferentIteratorsError("HashMap::Iterator::operator !=");
        
        return current != rhsASI->current;
    }
    
    template<class KEY,class T>
    ics::pair<KEY,T>& HashMap<KEY,T>::Iterator::operator *() const {
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("HashMap::Iterator::operator *");
        if (!can_erase || current.second == nullptr)
            throw IteratorPositionIllegal("HashMap::Iterator::operator * Iterator illegal: exhausted");
        
        return current.second->value;
    }
    
    template<class KEY,class T>
    ics::pair<KEY,T>* HashMap<KEY,T>::Iterator::operator ->() const {
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("HashMap::Iterator::operator *");
        if (!can_erase || current.second == nullptr)
            throw IteratorPositionIllegal("HashMap::Iterator::operator -> Iterator illegal: exhausted");
        
        return &current.second->value;
    }
    
}

#endif /* HASH_MAP_HPP_ */
