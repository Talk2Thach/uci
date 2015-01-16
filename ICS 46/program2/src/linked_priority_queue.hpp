//Tianya Chen UID=756681
//Edward Xia  UID=149235
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming
#ifndef LINKED_PRIORITY_QUEUE_HPP_
#define LINKED_PRIORITY_QUEUE_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "priority_queue.hpp"
#include "array_stack.hpp"


namespace ics {
    
    template<class T> class LinkedPriorityQueue : public PriorityQueue<T>  {
        using PriorityQueue<T>::gt;  //Required because of templated classes
    public:
        LinkedPriorityQueue() = delete;
        explicit LinkedPriorityQueue(bool (*agt)(const T& a, const T& b));
        LinkedPriorityQueue(const LinkedPriorityQueue<T>& to_copy);
        LinkedPriorityQueue(std::initializer_list<T> il,bool (*agt)(const T& a, const T& b));
        LinkedPriorityQueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop,bool (*agt)(const T& a, const T& b));
        virtual ~LinkedPriorityQueue();
        
        virtual bool empty      () const;
        virtual int  size       () const;
        virtual T&   peek       () const;
        virtual std::string str () const;
        
        virtual int  enqueue (const T& element);
        virtual T    dequeue ();
        virtual void clear   ();
        
        virtual int enqueue (ics::Iterator<T>& start, const ics::Iterator<T>& stop);
        
        virtual LinkedPriorityQueue<T>& operator = (const LinkedPriorityQueue<T>& rhs);
        virtual bool operator == (const PriorityQueue<T>& rhs) const;
        virtual bool operator != (const PriorityQueue<T>& rhs) const;
        
        template<class T2>
        friend std::ostream& operator << (std::ostream& outs, const LinkedPriorityQueue<T2>& s);
        
    private:
        class LN;
        
    public:
        class Iterator : public ics::Iterator<T> {
        public:
            //KLUDGE should be callable only in begin/end
            Iterator(LinkedPriorityQueue<T>* fof, LN* initial);
            virtual ~Iterator();
            virtual T           erase();
            virtual std::string str  () const;
            virtual const ics::Iterator<T>& operator ++ ();
            virtual const ics::Iterator<T>& operator ++ (int);
            virtual bool operator == (const ics::Iterator<T>& rhs) const;
            virtual bool operator != (const ics::Iterator<T>& rhs) const;
            virtual T& operator *  () const;
            virtual T* operator -> () const;
        private:
            LN*                     prev;     //if header, then current is at front of list
            LN*                     current;  //if can_erase is false, this value is unusable
            LinkedPriorityQueue<T>* ref_pq;
            int                     expected_mod_count;
            bool                    can_erase = true;
        };
        
        //For explicit use: Iterator<...>& it = c.ibegin(); ... or for (Iterator<...>& it = c.ibegin(); it != c.iend(); ++it)...
        virtual ics::Iterator<T>& ibegin () const;
        virtual ics::Iterator<T>& iend   () const;
        
        //For implicit use: for (... i : c)...
        virtual Iterator begin () const;
        virtual Iterator end   () const;
        
    private:
        class LN {
        public:
            LN ()                      {}
            LN (const LN& ln)          : value(ln.value), next(ln.next){}
            LN (T v,  LN* n = nullptr) : value(v), next(n){}
            
            T   value;
            LN* next = nullptr;
        };
        
        //See base class PriorityQueue
        //bool (*gt)(const T& a, const T& b);// gt(a,b) = true iff a has higher priority than b
        int used      =  0;
        LN* front     =  new LN();
        int mod_count =  0;                  //For sensing concurrent modification
        void delete_list(LN*& front);        //Recycle storage, set front's argument to nullptr;
    };
    
    
    
    //See code in array_priority_queue.hpp and linked_queue.hpp
    
    //Write the constructors, methods, and operators here for LinkedPriorityQueue
    //Fill in the missing parts of the erase method and ++ operators
    //  for LinkedPriorityQueue's Iterator
    template<class T>
    LinkedPriorityQueue<T>::LinkedPriorityQueue(bool (*agt)(const T& a, const T& b)) : PriorityQueue<T>(agt) {
    }
    
    
    template<class T>
    LinkedPriorityQueue<T>::LinkedPriorityQueue(const LinkedPriorityQueue<T>& to_copy) : PriorityQueue<T>(to_copy.gt) {
        for (LN *src_node = to_copy.front, *dest_node = front; src_node->next != nullptr; src_node = src_node->next, dest_node = dest_node->next) {
            dest_node->next = new LN(src_node->next->value, nullptr);
        }
        used = to_copy.used;
    }
    
    
    template<class T>
    LinkedPriorityQueue<T>::LinkedPriorityQueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop, bool (*agt)(const T& a, const T& b)) : PriorityQueue<T>(agt) {
        enqueue(start,stop);
    }
    
    
    template<class T>
    LinkedPriorityQueue<T>::LinkedPriorityQueue(std::initializer_list<T> il, bool (*agt)(const T& a, const T& b)) : PriorityQueue<T>(agt)  {
        for (T q_elem : il)
            enqueue(q_elem);
    }
    
    
    template<class T>
    LinkedPriorityQueue<T>::~LinkedPriorityQueue() {
        delete_list(front);
    }
    
    
    template<class T>
    bool LinkedPriorityQueue<T>::empty() const {
        return used == 0;
    }
    
    
    template<class T>
    inline int LinkedPriorityQueue<T>::size() const {
        return used;
    }
    
    
    template<class T>
    T& LinkedPriorityQueue<T>::peek () const {
        if (this->empty())
            throw EmptyError("LinkedQueue::peek");
        
        return front->next->value;
    }
    
    
    template<class T>
    std::string LinkedPriorityQueue<T>::str() const {
        std::ostringstream answer;
        answer << *this << "(length=" << used << ",front=" << front << ",mod_count=" << mod_count << ")";
        return answer.str();
    }
    
    
    template<class T>
    int LinkedPriorityQueue<T>::enqueue(const T& element) {
        LN *node = front;
        while (node->next != nullptr && gt(node->next->value, element)) {
            node = node->next;
        }
        node->next = new LN(element, node->next);
        ++used;
        ++mod_count;
        return 1;
    }
    
    
    template<class T>
    T LinkedPriorityQueue<T>::dequeue() {
        if (this->empty())
            throw EmptyError("LinkedQueue::dequeue");
        T answer = front->next->value;
        LN *next = front->next->next;
        delete front->next;
        front->next = next;
        --used;
        ++mod_count;
        return answer;
    }
    
    
    template<class T>
    void LinkedPriorityQueue<T>::clear() {
        delete_list(front->next);
        front->next = nullptr;
        used = 0;
        ++mod_count;
    }
    
    
    template<class T>
    int LinkedPriorityQueue<T>::enqueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
        int count = 0;
        for (; start != stop; ++start)
            count += enqueue(*start);
        
        return count;
    }
    
    
    template<class T>
    LinkedPriorityQueue<T>& LinkedPriorityQueue<T>::operator = (const LinkedPriorityQueue<T>& rhs) {
        delete_list(front->next);
        gt = rhs.gt;
        front->next = nullptr;
        for (LN *src_node = rhs.front, *dest_node = front; src_node->next != nullptr; src_node = src_node->next, dest_node = dest_node->next) {
            dest_node->next = new LN(src_node->next->value, nullptr);
        }
        used = rhs.used;
        ++mod_count;
        return *this;
    }
    
    
    template<class T>
    bool LinkedPriorityQueue<T>::operator == (const PriorityQueue<T>& rhs) const {
        if (this == &rhs)
            return true;
        if (used != rhs.size() || gt != rhs.gt)
            return false;
        for (auto &this_i = ibegin(), &rhs_i = rhs.ibegin(); this_i != iend() && rhs_i != rhs.iend(); ++this_i, ++rhs_i) {
            if (*this_i != *rhs_i) {
                return false;
            }
        }
        return true;
    }
    
    template<class T>
    bool LinkedPriorityQueue<T>::operator != (const PriorityQueue<T>& rhs) const {
        return !(*this == rhs);
    }
    
    template<class T>
    std::ostream& operator << (std::ostream& outs, const LinkedPriorityQueue<T>& q) {
        outs << "priority_queue[";
        if (!q.empty()) {
            T **t_array  = new T*[q.used]; // use pointers to avoid copy objects, reduce memory usage.
            size_t index = q.used;
            for (auto *node = q.front->next; node != nullptr; node = node->next) {
                t_array[--index] = &node->value;
            }
            outs << *t_array[0];
            for (size_t index = 1; index < q.used; ++index) {
                outs << "," << *t_array[index];
            }
            delete [] t_array;
        }
        outs << "]:highest";
        return outs;
    }
    
    template<class T>
    void LinkedPriorityQueue<T>::delete_list(LN*& front) {
        while (front != nullptr) {
            LN *next = front->next;
            delete front;
            front = next;
        }
    }
    
    //KLUDGE: memory-leak
    template<class T>
    auto LinkedPriorityQueue<T>::ibegin () const -> ics::Iterator<T>& {
        return *(new Iterator(const_cast<LinkedPriorityQueue<T>*>(this),front->next));
    }
    
    //KLUDGE: memory-leak
    template<class T>
    auto LinkedPriorityQueue<T>::iend () const -> ics::Iterator<T>& {
        return *(new Iterator(const_cast<LinkedPriorityQueue<T>*>(this),nullptr));
    }
    
    template<class T>
    auto LinkedPriorityQueue<T>::begin () const -> LinkedPriorityQueue<T>::Iterator {
        return Iterator(const_cast<LinkedPriorityQueue<T>*>(this),front->next);
    }
    
    template<class T>
    auto LinkedPriorityQueue<T>::end () const -> LinkedPriorityQueue<T>::Iterator {
        return Iterator(const_cast<LinkedPriorityQueue<T>*>(this),nullptr);
    }
    
    
    
    template<class T>
    LinkedPriorityQueue<T>::Iterator::Iterator(LinkedPriorityQueue<T>* fof, LN* initial) : current(initial), ref_pq(fof) {
        prev = ref_pq->front;
        expected_mod_count = ref_pq->mod_count;
    }
    
    template<class T>
    LinkedPriorityQueue<T>::Iterator::~Iterator() {}
    
    template<class T>
    T LinkedPriorityQueue<T>::Iterator::erase() {
        if (expected_mod_count != ref_pq->mod_count)
            throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::erase");
        if (!can_erase)
            throw CannotEraseError("LinkedPriorityQueue::Iterator::erase Iterator cursor already erased");
        if (current == nullptr)
            throw CannotEraseError("LinkedPriorityQueue::Iterator::erase Iterator cursor beyond data structure");
        
        //Fill in the rest of the code here
        can_erase = false;
        LN *to_erase = current;
        T answer = current->value;
        prev->next = current->next;
        current = current->next;
        delete to_erase;
        --ref_pq->used;
        return answer;
    }
    
    template<class T>
    std::string LinkedPriorityQueue<T>::Iterator::str() const {
        std::ostringstream answer;
        answer << ref_pq->str() << "(current=" << current << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
        return answer.str();
    }
    
    template<class T>
    const ics::Iterator<T>& LinkedPriorityQueue<T>::Iterator::operator ++ () {
        if (expected_mod_count != ref_pq->mod_count)
            throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator ++");
        
        //Fill in the rest of the code here
        if (!can_erase) {
            can_erase = true;
            return *this;
        }
        if (current == nullptr) {
            return *this;
        }
        prev = current;
        current = current->next;
        return *this;
    }
    
    //KLUDGE: can create garbage! (can return local value!)
    template<class T>
    const ics::Iterator<T>& LinkedPriorityQueue<T>::Iterator::operator ++ (int) {
        if (expected_mod_count != ref_pq->mod_count)
            throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator ++(int)");
        
        if (current == nullptr)
            return *this;
        
        //Fill in the rest of the code here
        if (!can_erase) {
            can_erase = true;
            return *(new Iterator(const_cast<LinkedPriorityQueue<T>*>(ref_pq),prev));
        }
        LN* node = current;
        prev = current;
        current = current->next;
        return *(new Iterator(const_cast<LinkedPriorityQueue<T>*>(ref_pq),node));
    }
    
    template<class T>
    bool LinkedPriorityQueue<T>::Iterator::operator == (const ics::Iterator<T>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("LinkedPriorityQueue::Iterator::operator ==");
        if (expected_mod_count != ref_pq->mod_count)
            throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator ==");
        if (ref_pq != rhsASI->ref_pq)
            throw ComparingDifferentIteratorsError("LinkedPriorityQueue::Iterator::operator ==");
        
        return current == rhsASI->current;
    }
    
    
    template<class T>
    bool LinkedPriorityQueue<T>::Iterator::operator != (const ics::Iterator<T>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("LinkedPriorityQueue::Iterator::operator !=");
        if (expected_mod_count != ref_pq->mod_count)
            throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator !=");
        if (ref_pq != rhsASI->ref_pq)
            throw ComparingDifferentIteratorsError("LinkedPriorityQueue::Iterator::operator !=");
        
        return current != rhsASI->current;
    }
    
    template<class T>
    T& LinkedPriorityQueue<T>::Iterator::operator *() const {
        if (expected_mod_count != ref_pq->mod_count)
            throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator *");
        if (!can_erase || current == nullptr) {
            std::ostringstream where;
            where << current
            << " when front = " << ref_pq->front;
            throw IteratorPositionIllegal("LinkedPriorityQueue::Iterator::operator * Iterator illegal: "+where.str());
        }
        
        return current->value;
    }
    
    template<class T>
    T* LinkedPriorityQueue<T>::Iterator::operator ->() const {
        if (expected_mod_count != ref_pq->mod_count)
            throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator *");
        if (!can_erase || current == nullptr) {
            std::ostringstream where;
            where << current
            << " when front = " << ref_pq->front;
            throw IteratorPositionIllegal("LinkedPriorityQueue::Iterator::operator * Iterator illegal: "+where.str());
        }
        
        return &(current->value);
    }
    
}

#endif /* LINKED_PRIORITY_QUEUE_HPP_ */
