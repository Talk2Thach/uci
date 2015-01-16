//Tianya Chen UID=756681
//Edward Xia  UID=149235
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming
#ifndef LINKED_QUEUE_HPP_
#define LINKED_QUEUE_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "queue.hpp"


namespace ics {
    
    template<class T> class LinkedQueue : public Queue<T>  {
    public:
        LinkedQueue();
        LinkedQueue(const LinkedQueue<T>& to_copy);
        LinkedQueue(std::initializer_list<T> il);
        LinkedQueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop);
        virtual ~LinkedQueue();
        
        virtual bool empty      () const;
        virtual int  size       () const;
        virtual T&   peek       () const;
        virtual std::string str () const;
        
        virtual int  enqueue (const T& element);
        virtual T    dequeue ();
        virtual void clear   ();
        
        virtual int enqueue (ics::Iterator<T>& start, const ics::Iterator<T>& stop);
        
        virtual LinkedQueue<T>& operator = (const LinkedQueue<T>& rhs);
        virtual bool operator == (const Queue<T>& rhs) const;
        virtual bool operator != (const Queue<T>& rhs) const;
        
        template<class T2>
        friend std::ostream& operator << (std::ostream& outs, const LinkedQueue<T2>& s);
        
    private:
        class LN;
        
    public:
        class Iterator : public ics::Iterator<T> {
        public:
            //KLUDGE should be callable only in begin/end
            Iterator(LinkedQueue<T>* fof, LN* initial);
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
            LN*             prev = nullptr;  //if nullptr, current at front of list
            LN*             current;         //if can_erase is false, this value is unusable
            LinkedQueue<T>* ref_queue;
            int             expected_mod_count;
            bool            can_erase = true;
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
        
        int used      =  0;
        LN* front     =  nullptr;
        LN* rear      =  nullptr;
        int mod_count =  0;            //For sensing of concurrent modification
        void delete_list(LN*& front);  //Recycle storage, set front's argument to nullptr;
    };
    
    
    
    //See code in array_queue.hpp
    
    //Write the constructors, methods, and operators here for LinkedQueue
    //Fill in the missing parts of the erase method and ++ operators
    //  for LinkedQueue's Iterator
    template<class T>
    LinkedQueue<T>::LinkedQueue() {
    }
    
    
    template<class T>
    LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& to_copy)  {
        if (to_copy.front != nullptr) {
            front = new LN(to_copy.front->value, nullptr);
            rear = front;
            for (LN *src_node = to_copy.front; src_node->next != nullptr; src_node = src_node->next, rear = rear->next) {
                rear->next = new LN(src_node->next->value, nullptr);
            }
            used = to_copy.used;
        }
    }
    
    
    template<class T>
    LinkedQueue<T>::LinkedQueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
        enqueue(start,stop);
    }
    
    
    template<class T>
    LinkedQueue<T>::LinkedQueue(std::initializer_list<T> il) {
        for (T q_elem : il)
            enqueue(q_elem);
    }
    
    
    template<class T>
    LinkedQueue<T>::~LinkedQueue() {
        delete_list(front);
    }
    
    
    template<class T>
    bool LinkedQueue<T>::empty() const {
        return used == 0;
    }
    
    
    template<class T>
    inline int LinkedQueue<T>::size() const {
        return used;
    }
    
    
    template<class T>
    T& LinkedQueue<T>::peek () const {
        if (empty())
            throw EmptyError("LinkedQueue::peek");
        
        return front->value;
    }
    
    
    template<class T>
    std::string LinkedQueue<T>::str() const {
        std::ostringstream answer;
        if (used == 0) {
            answer << "queue[]";
        } else {
            answer << "queue[";
            for (auto &it = ibegin(); it != iend(); ) {
                answer << *it;
                if (++it != iend()) {
                    answer << ",";
                } else {
                    answer << "]";
                }
            }
        }
        answer << "(length=" << used << ",front=" << front << ",rear=" << rear << ",mod_count=" << mod_count << ")";
        return answer.str();
    }
    
    
    template<class T>
    int LinkedQueue<T>::enqueue(const T& element) {
        if (rear == nullptr) {
            front = new LN(element, nullptr);
            rear = front;
        } else {
            rear->next = new LN(element, nullptr);
            rear = rear->next;
        }
        ++used;
        ++mod_count;
        return 1;
    }
    
    
    template<class T>
    T LinkedQueue<T>::dequeue() {
        if (this->empty())
            throw EmptyError("LinkedQueue::dequeue");
        T answer = front->value;
        LN *next = front->next;
        delete front;
        front = next;
        if (front == nullptr) {
            rear = front;
        }
        --used;
        ++mod_count;
        return answer;
    }
    
    
    template<class T>
    void LinkedQueue<T>::clear() {
        delete_list(front);
        front = nullptr;
        rear  = nullptr;
        used = 0;
        ++mod_count;
    }
    
    
    template<class T>
    int LinkedQueue<T>::enqueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
        int count = 0;
        for (; start != stop; ++start)
            count += enqueue(*start);
        
        return count;
    }
    
    
    template<class T>
    LinkedQueue<T>& LinkedQueue<T>::operator = (const LinkedQueue<T>& rhs) {
        delete_list(front);
        front = nullptr;
        rear  = nullptr;
        if (rhs.front != nullptr) {
            front = new LN(rhs.front->value, nullptr);
            rear = front;
            for (LN *src_node = rhs.front; src_node->next != nullptr; src_node = src_node->next, rear = rear->next) {
                rear->next = new LN(src_node->next->value, nullptr);
            }
        }
        used = rhs.used;
        ++mod_count;
        return *this;
    }
    
    
    template<class T>
    bool LinkedQueue<T>::operator == (const Queue<T>& rhs) const {
        if (this == &rhs)
            return true;
        if (used != rhs.size())
            return false;
        for (auto &this_i = ibegin(), &rhs_i = rhs.ibegin(); this_i != iend() && rhs_i != rhs.iend(); ++this_i, ++rhs_i) {
            if (*this_i != *rhs_i) {
                return false;
            }
        }
        return true;
    }
    
    template<class T>
    bool LinkedQueue<T>::operator != (const Queue<T>& rhs) const {
        return !(*this == rhs);
    }
    
    template<class T>
    std::ostream& operator << (std::ostream& outs, const LinkedQueue<T>& q) {
        outs << "queue[";
        
        if (!q.empty()) {
            outs << q.peek();
            auto &i = q.ibegin();
            for (++i; i != q.iend(); ++i) {
                outs << ","<< *i;
            }
        }
        
        outs << "]:rear";
        return outs;
    }
    
    template<class T>
    void LinkedQueue<T>::delete_list(LN*& front) {
        while (front != nullptr) {
            LN *next = front->next;
            delete front;
            front = next;
        }
    }
    
    
    
    //KLUDGE: memory-leak
    template<class T>
    auto LinkedQueue<T>::ibegin () const -> ics::Iterator<T>& {
        return *(new Iterator(const_cast<LinkedQueue<T>*>(this),front));
    }
    
    //KLUDGE: memory-leak
    template<class T>
    auto LinkedQueue<T>::iend () const -> ics::Iterator<T>& {
        return *(new Iterator(const_cast<LinkedQueue<T>*>(this),nullptr));
    }
    
    template<class T>
    auto LinkedQueue<T>::begin () const -> LinkedQueue<T>::Iterator {
        return Iterator(const_cast<LinkedQueue<T>*>(this),front);
    }
    
    template<class T>
    auto LinkedQueue<T>::end () const -> LinkedQueue<T>::Iterator {
        return Iterator(const_cast<LinkedQueue<T>*>(this),nullptr);
    }
    
    
    
    template<class T>
    LinkedQueue<T>::Iterator::Iterator(LinkedQueue<T>* fof, LN* initial) : current(initial), ref_queue(fof) {
        expected_mod_count = ref_queue->mod_count;
    }
    
    template<class T>
    LinkedQueue<T>::Iterator::~Iterator() {}
    
    template<class T>
    T LinkedQueue<T>::Iterator::erase() {
        if (expected_mod_count != ref_queue->mod_count)
            throw ConcurrentModificationError("LinkedQueue::Iterator::erase");
        if (!can_erase)
            throw CannotEraseError("LinkedQueue::Iterator::erase Iterator cursor already erased");
        if (current == nullptr)
            throw CannotEraseError("LinkedQueue::Iterator::erase Iterator cursor beyond data structure");
        
        //Fill in the rest of the code here
        can_erase = false;
        LN *to_erase = current;
        T answer = to_erase->value;
        if (current == ref_queue->front) {
            ref_queue->front = current->next;
        }
        if (current == ref_queue->rear) {
            ref_queue->rear = prev;
        }
        if (prev != nullptr) {
            prev->next = current->next;
        }
        current = current->next;
        delete to_erase;
        --ref_queue->used;
        return answer;
    }
    
    template<class T>
    std::string LinkedQueue<T>::Iterator::str() const {
        std::ostringstream answer;
        answer << ref_queue->str() << "(current=" << current << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
        return answer.str();
    }
    
    template<class T>
    const ics::Iterator<T>& LinkedQueue<T>::Iterator::operator ++ () {
        if (expected_mod_count != ref_queue->mod_count)
            throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++");
        
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
    const ics::Iterator<T>& LinkedQueue<T>::Iterator::operator ++ (int) {
        if (expected_mod_count != ref_queue->mod_count)
            throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++(int)");
        
        //Fill in the rest of the code here
        if (current == nullptr) {
            return *this;
        }
        
        if (!can_erase) {
            can_erase = true;
            return *(new Iterator(const_cast<LinkedQueue<T>*>(ref_queue),prev));
        }
        LN* node = current;
        prev = current;
        current = current->next;
        return *(new Iterator(const_cast<LinkedQueue<T>*>(ref_queue),node));
    }
    
    template<class T>
    bool LinkedQueue<T>::Iterator::operator == (const ics::Iterator<T>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("LinkedQueue::Iterator::operator ==");
        if (expected_mod_count != ref_queue->mod_count)
            throw ConcurrentModificationError("LinkedQueue::Iterator::operator ==");
        if (ref_queue != rhsASI->ref_queue)
            throw ComparingDifferentIteratorsError("LinkedQueue::Iterator::operator ==");
        
        return current == rhsASI->current;
    }
    
    
    template<class T>
    bool LinkedQueue<T>::Iterator::operator != (const ics::Iterator<T>& rhs) const {
        const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
        if (rhsASI == 0)
            throw IteratorTypeError("LinkedQueue::Iterator::operator !=");
        if (expected_mod_count != ref_queue->mod_count)
            throw ConcurrentModificationError("LinkedQueue::Iterator::operator !=");
        if (ref_queue != rhsASI->ref_queue)
            throw ComparingDifferentIteratorsError("LinkedQueue::Iterator::operator !=");
        
        return current != rhsASI->current;
    }
    
    template<class T>
    T& LinkedQueue<T>::Iterator::operator *() const {
        if (expected_mod_count != ref_queue->mod_count)
            throw ConcurrentModificationError("LinkedQueue::Iterator::operator *");
        if (!can_erase || current == nullptr) {
            std::ostringstream where;
            where << current
            << " when front = " << ref_queue->front << " and "
            << " and rear = " << ref_queue->rear;
            throw IteratorPositionIllegal("LinkedQueue::Iterator::operator * Iterator illegal: "+where.str());
        }
        
        return current->value;
    }
    
    template<class T>
    T* LinkedQueue<T>::Iterator::operator ->() const {
        if (expected_mod_count != ref_queue->mod_count)
            throw ConcurrentModificationError("LinkedQueue::Iterator::operator *");
        if (!can_erase || current == nullptr) {
            std::ostringstream where;
            where << current
            << " when front = " << ref_queue->front << " and "
            << " and rear = " << ref_queue->rear;
            throw IteratorPositionIllegal("LinkedQueue::Iterator::operator * Iterator illegal: "+where.str());
        }
        
        return &(current->value);
    }
    
}

#endif /* LINKED_QUEUE_HPP_ */
