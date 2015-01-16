//Tianya Chen UID=756681
//Edward Xia  UID=149235
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming
#ifndef BST_MAP_HPP_
#define BST_MAP_HPP_

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
    
    template<class KEY,class T> class BSTMap : public Map<KEY,T>	{
    public:
        typedef ics::pair<KEY,T> Entry;
        BSTMap();
        BSTMap(const BSTMap<KEY,T>& to_copy);
        BSTMap(std::initializer_list<Entry> il);
        BSTMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop);
        virtual ~BSTMap();
        
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
        virtual BSTMap<KEY,T>& operator = (const BSTMap<KEY,T>& rhs);
        virtual bool operator == (const Map<KEY,T>& rhs) const;
        virtual bool operator != (const Map<KEY,T>& rhs) const;
        
        template<class KEY2,class T2>
        friend std::ostream& operator << (std::ostream& outs, const BSTMap<KEY2,T2>& m);
        
        virtual ics::Iterator<Entry>& ibegin () const;
        virtual ics::Iterator<Entry>& iend   () const;
        
    private:
        class TN;
        
    public:
        class Iterator : public ics::Iterator<Entry> {
        public:
            //KLUDGE should be callable only in begin/end
            Iterator(BSTMap<KEY,T>* iterate_over, bool begin);
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
            ics::ArrayQueue<Entry> it;          //Iterator (as a Queue) for Map
            BSTMap<KEY,T>*         ref_map;
            int                    expected_mod_count;
            bool                   can_erase = true;
        };
        
        virtual Iterator begin () const;
        virtual Iterator end   () const;
        //KLUDGE: define
        //virtual ics::Iterator<KEY>&  begin_key   () const;
        //virtual ics::Iterator<KEY>&  end_key     () const;
        //virtual ics::Iterator<T>&    begin_value () const;
        //virtual ics::Iterator<T>&    end_value   () const;
        
    private:
        class TN {
        public:
            TN ()                     : left(nullptr), right(nullptr){}
            TN (const TN& tn)         : value(tn.value), left(tn.left), right(tn.right){}
            TN (Entry v, TN* l = nullptr,
                TN* r = nullptr) : value(v), left(l), right(r){}
            
            Entry value;
            TN*   left;
            TN*   right;
        };
        
        TN* map       = nullptr;
        int used      = 0; //Amount of array used
        int mod_count = 0; //For sensing concurrent modification
        TN*  find_key      (TN*  root, const KEY& key) const;
        bool find_value    (TN*  root, const T& value) const;
        T&    insert       (TN*& root, const KEY& key, const T& value);
        ics::pair<KEY,T> remove_closest(TN*& root);
        T    remove        (TN*& root, const KEY& key);
        TN*  copy          (TN*  root)                 const;
        void copy_to_queue (TN* root, ArrayQueue<Entry>& q) const;
        void delete_BST    (TN*& root);
        bool equals        (TN*  root, const Map<KEY,T>& other) const;
        std::string string_rotated(TN* root, std::string indent) const;
    };
    
    
    
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::BSTMap() {}
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::BSTMap(const BSTMap<KEY,T>& to_copy) : used(to_copy.used) {
        map = copy(to_copy.map);
    }
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::BSTMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop) {
        for (; start != stop; ++start) {
            put(start->first, start->second);
        }
    }
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::BSTMap(std::initializer_list<Entry> il) {
        for (Entry m_entry : il) {
            put(m_entry.first,m_entry.second);
        }
    }
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::~BSTMap() {
        delete_BST(map);
    }
    
    
    template<class KEY,class T>
    inline bool BSTMap<KEY,T>::empty() const {
        return used == 0;
    }
    
    
    template<class KEY,class T>
    int BSTMap<KEY,T>::size() const {
        return used;
    }
    
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::has_key (const KEY& element) const {
        return find_key(map, element) != nullptr;
    }
    
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::has_value (const T& element) const {
        return find_value(map, element);
    }
    
    
    template<class KEY,class T>
    std::string BSTMap<KEY,T>::str() const {
        std::ostringstream answer;
        answer << *this;
        return answer.str();
    }
    
    
    template<class KEY,class T>
    T BSTMap<KEY,T>::put(const KEY& key, const T& value) {
        TN* node = find_key(map, key);
        if (node != nullptr) {
            ++mod_count;
            T result = node->value.second;
            node->value.second = value;
            return result;
        } else {
            ++used;
            ++mod_count;
            return insert(map, key, value);
        }
    }
    
    template<class KEY,class T>
    T BSTMap<KEY,T>::erase(const KEY& key) {
        T result = remove(map, key);
        --used;
        ++mod_count;
        return result;
    }
    
    
    template<class KEY,class T>
    void BSTMap<KEY,T>::clear() {
        used = 0;
        ++mod_count;
        delete_BST(map);
        map = nullptr;
    }
    
    
    template<class KEY,class T>
    int BSTMap<KEY,T>::put (ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop) {
        int count = 0;
        for (; start != stop; ++start) {
            ++count;
            put(start->first, start->second);
        }
        return count;
    }
    
    
    template<class KEY,class T>
    T& BSTMap<KEY,T>::operator [] (const KEY& key) {
        TN *node = find_key(map, key);
        if (node != nullptr) {
            return node->value.second;
        }
        ++used;
        ++mod_count;
        return insert(map, key, T());
        
    }
    
    
    template<class KEY,class T>
    const T& BSTMap<KEY,T>::operator [] (const KEY& key) const {
        TN *node = find_key(map, key);
        if (node != nullptr) {
            return node->value.second;
        }
        
        std::ostringstream answer;
        answer << "BSTMap::operator []: key(" << key << ") not in Map";
        throw KeyError(answer.str());
    }
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::operator == (const Map<KEY,T>& rhs) const {
        if (this == &rhs)
            return true;
        if (used != rhs.size())
            return false;

        return equals(map, rhs);
    }
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>& BSTMap<KEY,T>::operator = (const BSTMap<KEY,T>& rhs) {
        if (this == &rhs) {
            return *this;
        }
        clear();
        used = rhs.used;
        map = copy(rhs.map);
        return *this;
    }
    
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::operator != (const Map<KEY,T>& rhs) const {
        return !(*this == rhs);
    }
    
    
    template<class KEY,class T>
    std::ostream& operator << (std::ostream& outs, const BSTMap<KEY,T>& m) {
        outs << "map[";
        
        if (!m.empty()) {
            ics::ArrayQueue<ics::pair<KEY,T>> q;
            m.copy_to_queue(m.map, q);
            //m.map[i] couts as map[pair[key,value]]
            auto &it = q.ibegin();
            outs << it->first << "->" << it->second;
            for (++it; it != q.iend(); ++it) {
                outs << "," << it->first << "->" << it->second;
            }
        }
        
        outs << "]";
        return outs;
    }
    
    
    //KLUDGE: memory-leak
    template<class KEY,class T>
    auto BSTMap<KEY,T>::ibegin () const -> ics::Iterator<Entry>& {
        return *(new Iterator(const_cast<BSTMap<KEY,T>*>(this),true));
    }
    
    
    //KLUDGE: memory-leak
    template<class KEY,class T>
    auto BSTMap<KEY,T>::iend () const -> ics::Iterator<Entry>& {
        return *(new Iterator(const_cast<BSTMap<KEY,T>*>(this),false));
    }
    
    
    template<class KEY,class T>
    auto BSTMap<KEY,T>::begin () const -> BSTMap<KEY,T>::Iterator {
        return Iterator(const_cast<BSTMap<KEY,T>*>(this),true);
    }
    
    
    template<class KEY,class T>
    auto BSTMap<KEY,T>::end () const -> BSTMap<KEY,T>::Iterator {
        return Iterator(const_cast<BSTMap<KEY,T>*>(this),false);
    }
    
    
    template<class KEY,class T>
    typename BSTMap<KEY,T>::TN* BSTMap<KEY,T>::find_key (TN* root, const KEY& key) const {
        if (root != nullptr) {
            if (root->value.first == key) {
                return root;
            } else if (root->value.first > key) {
                return find_key(root->left, key);
            } else if (root->value.first < key) {
                return find_key(root->right, key);
            }
        }
        return nullptr;
    }
    
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::find_value (TN* root, const T& value) const {
        return root != nullptr && (root->value.second == value || find_value(root->left, value) || find_value(root->right, value));
    }
    
    
    template<class KEY,class T>
    T& BSTMap<KEY,T>::insert (TN*& root, const KEY& key, const T& value) {
        if (root == nullptr) {
            root = new TN(Entry{key, value}, nullptr, nullptr);
            return root->value.second;
        } else if (key < root->value.first) {
            return insert(root->left, key, value);
        } else if (key > root->value.first) {
            return insert(root->right, key, value);
        } else {
            root->value.second = value;
            return root->value.second;
        }
    }
    
    
    template<class KEY,class T>
    ics::pair<KEY,T> BSTMap<KEY,T>::remove_closest(TN*& root) {
        if (root->right == nullptr) {
            ics::pair<KEY,T> to_return = root->value;
            TN* to_delete = root;
            root = root->left;
            delete to_delete;
            return to_return;
        }else
            return remove_closest(root->right);
    }
    
    
    template<class KEY,class T>
    T BSTMap<KEY,T>::remove (TN*& root, const KEY& key) {
        if (root == nullptr) {
            std::ostringstream answer;
            answer << "BSTMap::erase: key(" << key << ") not in Map";
            throw KeyError(answer.str());
        }else
            if (key == root->value.first) {
                T to_return = root->value.second;
                if (root->left == nullptr) {
                    TN* to_delete = root;
                    root = root->right;
                    delete to_delete;
                }else if (root->right == nullptr) {
                    TN* to_delete = root;
                    root = root->left;
                    delete to_delete;
                }else
                    root->value = remove_closest(root->left);
                return to_return;
            }else
                return remove( (key < root->value.first ? root->left : root->right), key);
    }
    
    
    template<class KEY,class T>
    typename BSTMap<KEY,T>::TN* BSTMap<KEY,T>::copy (TN* root) const {
        if (root != nullptr) {
            return new TN(root->value, copy(root->left), copy(root->right));
        } else {
            return nullptr;
        }
    }
    
    
    template<class KEY,class T>
    void BSTMap<KEY,T>::copy_to_queue (TN* root, ArrayQueue<Entry>& q) const {
        if (root != nullptr) {
            copy_to_queue(root->left, q);
            q.enqueue(root->value);
            copy_to_queue(root->right, q);
        }
    }
    
    
    template<class KEY,class T>
    void BSTMap<KEY,T>::delete_BST (TN*& root) {
        if (root != nullptr) {
            delete_BST(root->left);
            delete_BST(root->right);
            delete root;
        }
    }
    
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::equals (TN*  root, const Map<KEY,T>& other) const {
        for (auto &it = other.ibegin(); it != other.iend(); ++it) {
            TN *node = find_key(root, it->first);
            if (node == nullptr || node->value.second != it->second) {
                return false;
            }
        }
        return true;
    }
    
    
    template<class KEY,class T>
    std::string BSTMap<KEY,T>::string_rotated(TN* root, std::string indent) const {
        if (root != nullptr) {
            return string_rotated(root->right, indent+"..") + indent + root->value + "\n" + string_rotated(root->left, indent+"..");
        }
        return "";
    }
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::Iterator::Iterator(BSTMap<KEY,T>* iterate_over, bool begin) : it(), ref_map(iterate_over) {
        if (begin) {
            iterate_over->copy_to_queue(iterate_over->map, it);
        }
        expected_mod_count = ref_map->mod_count;
    }
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::Iterator::Iterator(const Iterator& i) :
    it(i.it), ref_map(i.ref_map), expected_mod_count(i.expected_mod_count), can_erase(i.can_erase)
    {}
    
    
    template<class KEY,class T>
    BSTMap<KEY,T>::Iterator::~Iterator()
    {}
    
    
    template<class KEY,class T>
    auto BSTMap<KEY,T>::Iterator::erase() -> Entry {
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("BSTMap::Iterator::erase");
        if (!can_erase)
            throw CannotEraseError("BSTMap::Iterator::erase Iterator cursor already erased");
        if (it.empty())
            throw CannotEraseError("BSTMap::Iterator::erase Iterator cursor beyond data structure");
    
        can_erase = false;
        ref_map->erase(it.peek().first);
        expected_mod_count = ref_map->mod_count;
        return it.dequeue();
    }
    
    
    template<class KEY,class T>
    std::string BSTMap<KEY,T>::Iterator::str() const {
        std::ostringstream answer;
        answer << ref_map->str() << "(expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
        return answer.str();
    }
    
    
    //KLUDGE: cannot use Entry
    template<class KEY,class T>
    auto  BSTMap<KEY,T>::Iterator::operator ++ () -> const ics::Iterator<ics::pair<KEY,T>>& {
        if (expected_mod_count != ref_map->mod_count) {
            throw ConcurrentModificationError("BSTMap::Iterator::operator ++");
        }
        
        if (!can_erase) {
            can_erase = true;
        } else if (it.size() > 0) {
            it.dequeue();
        }
        return *this;
    }
    
    
    //KLUDGE: creates garbage! (can return local value!)
    template<class KEY,class T>
    auto BSTMap<KEY,T>::Iterator::operator ++ (int) -> const ics::Iterator<ics::pair<KEY,T>>&{
        if (expected_mod_count != ref_map->mod_count) {
            throw ConcurrentModificationError("BSTMap::Iterator::operator ++(int)");
        }
        
        Iterator* to_return = new Iterator(*this);
        if (!can_erase) {
            can_erase = true;
        } else if (it.size() > 0) {
            it.dequeue();
        }
        
        return *to_return;
    }
    
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::Iterator::operator == (const ics::Iterator<Entry>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("BSTMap::Iterator::operator ==");
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("BSTMap::Iterator::operator ==");
        if (ref_map != rhsASI->ref_map)
            throw ComparingDifferentIteratorsError("BSTMap::Iterator::operator ==");
        
        return it.size() == rhsASI->it.size();
    }
    
    
    template<class KEY,class T>
    bool BSTMap<KEY,T>::Iterator::operator != (const ics::Iterator<Entry>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("BSTMap::Iterator::operator !=");
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("BSTMap::Iterator::operator !=");
        if (ref_map != rhsASI->ref_map)
            throw ComparingDifferentIteratorsError("BSTMap::Iterator::operator !=");
        
        return it.size() != rhsASI->it.size();
    }
    
    
    template<class KEY,class T>
    ics::pair<KEY,T>& BSTMap<KEY,T>::Iterator::operator *() const {
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("BSTMap::Iterator::operator *");
        if (!can_erase || it.empty())
            throw IteratorPositionIllegal("BSTMap::Iterator::operator * Iterator illegal: exhausted");
        
        return it.peek();
    }
    
    
    template<class KEY,class T>
    ics::pair<KEY,T>* BSTMap<KEY,T>::Iterator::operator ->() const {
        if (expected_mod_count != ref_map->mod_count)
            throw ConcurrentModificationError("BSTMap::Iterator::operator *");
        if (!can_erase || it.empty())
            throw IteratorPositionIllegal("BSTMap::Iterator::operator -> Iterator illegal: exhausted");
        
        return &it.peek();
    }
    
    
}

#endif /* BST_MAP_HPP_ */
