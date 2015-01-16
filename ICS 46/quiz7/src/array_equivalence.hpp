#ifndef ARRAY_EQUIVALENCE_HPP_
#define ARRAY_EQUIVALENCE_HPP_

#include <sstream>
#include "ics_exceptions.hpp"
#include "array_map.hpp"
#include "array_set.hpp"


namespace ics {
    
    
    template<class T>
    class ArrayEquivalence {
    public:
        //Fundamental constructors/methods
        ArrayEquivalence();
        void add_singleton    (const T& a);
        bool in_same_class    (const T& a, const T& b);
        void merge_classes_of (const T& a, const T& b);
        
        //Other methods
        int size        () const;
        int class_count () const;
        ics::ArraySet<ics::ArraySet<T>> classes ();
        
        //Useful for debugging (bassed on the implementation)
        int max_height  () const;
        ics::ArrayMap<T,int> heights () const;
        void show_equivalence () const;
    private:
        ics::ArrayMap<T,T>   parent;
        ics::ArrayMap<T,int> root_size;
        T compress_to_root (T a);
    };
    
    
    
    template<class T>
    ArrayEquivalence<T>::ArrayEquivalence () : parent(), root_size() {
    }
    
    
    //Throw an EquivalenceError (with a descriptive message) if the parameter a
    //  already a value in the Equivalence (was previously added as a singleton)
    template<class T>
    void ArrayEquivalence<T>::add_singleton (const T& a) {
        if (parent.has_key(a)) {
            std::ostringstream exc;
            exc << "ArrayEquivalence.add_singleton: a(" << a << ") already in an equivalence class";
            throw EquivalenceError(exc.str());
        }
        parent[a]    = a;    //acts like its own parent
        root_size[a] = 1; //its equivalence class has 1 value in it
    }
    
    
    //Use compress_to_root in in_same_class and merge_classes_of
    //When finished, a and all its ancestors should refer
    //  (in the parent map) directly to the root of a's equivalence class
    //Throw an EquivalenceError (with a descriptive message) if the parameter a
    //  is not already a value in the Equivalence (was never added as a singleton)
    template<class T>
    T ArrayEquivalence<T>::compress_to_root (T a) {
        if (!parent.has_key(a)) {
            std::ostringstream error_message;
            error_message << "ArrayEquivalence.compress_to_root: a(" << a << ") is not in an equivalence class";
            throw EquivalenceError(error_message.str());
        }
        ics::ArraySet<T> classes;
        T root_of_a = parent[a];
        for (T child = a; root_of_a != child; child = parent[child], root_of_a = parent[child]) {
            classes.insert(child);
        }
        for (T child : classes) {
            parent[child] = root_of_a;
        }
        return root_of_a;
    }
    
    
    //Two values are in the same class if their equivalence trees have the
    //  same roots
    //In the process of finding the roots, compress all the values on the
    //  path to the root: make the parents of a and all its ancestors directly
    //  refer to the root of a's equivalance class (same for b).
    //Throw an EquivalenceError (with a descriptive message) if the parameter a or b
    //  is not already a value in the Equivalence (were never added as singletons)
    template<class T>
    bool ArrayEquivalence<T>::in_same_class (const T& a, const T& b) {
        if (!parent.has_key(a)) {
            std::ostringstream error_message;
            error_message << "ArrayEquivalence.in_same_class: a(" << a << ") is not in an equivalence class";
            throw EquivalenceError(error_message.str());
        }
        if (!parent.has_key(b)) {
            std::ostringstream error_message;
            error_message << "ArrayEquivalence.in_same_class: b(" << b << ") is not in an equivalence class";
            throw EquivalenceError(error_message.str());
        }
        return compress_to_root(a) == compress_to_root(b);
    }
    
    
    //Compress a and b to their roots.
    //If they are in different equivalence classes, make the parent of the
    //  root of the smaller equivalence class refer to the root of the larger
    //  equivalence class; update the size of the root of the larger equivalence
    //  class and remove the root of the smaller equivalence class from the root_size
    //Throw an EquivalenceError (with a descriptive message) if the parameter a or b
    //  is not already a value in the Equivalence (were never added as singletons)
    template<class T>
    void ArrayEquivalence<T>::merge_classes_of (const T& a, const T& b) {
        if (!parent.has_key(a)) {
            std::ostringstream error_message;
            error_message << "ArrayEquivalence.merge_classes_of: a(" << a << ") is not in an equivalence class";
            throw EquivalenceError(error_message.str());
        }
        if (!parent.has_key(b)) {
            std::ostringstream error_message;
            error_message << "ArrayEquivalence.merge_classes_of: b(" << b << ") is not in an equivalence class";
            throw EquivalenceError(error_message.str());
        }
        T root_of_a = compress_to_root(a), root_of_b = compress_to_root(b);
        if (root_size[root_of_a] >= root_size[root_of_b]) {
            parent[root_of_b] = root_of_a;
            root_size[root_of_a] += root_size.erase(root_of_b);
        } else {
            parent[root_of_a] = root_of_b;
            root_size[root_of_b] += root_size.erase(root_of_a);
        }
    }
    
    
    template<class T>
    int ArrayEquivalence<T>::size () const{
        return parent.size();
    }
    
    
    template<class T>
    int ArrayEquivalence<T>::class_count () const{
        return root_size.size();
    }
    
    
    template<class T>
    int ArrayEquivalence<T>::max_height () const{
        //Compute all root heights, then locate/return the largest
        int mh = 0;
        for (auto h : heights())
            if (h.second > mh)
                mh = h.second;
        return mh;
    }
    
    
    template<class T>
    ics::ArraySet<ics::ArraySet<T>> ArrayEquivalence<T>::classes () {
        ics::ArraySet<ics::ArraySet<T>>  classes;
        for (auto &root_kv : root_size) {
            ics::ArraySet<T> classes_of_root;
            for (auto &kv : parent) {
                if (compress_to_root(kv.first) == root_kv.first) {
                    classes_of_root.insert(kv.first);
                }
            }
            classes.insert(classes_of_root);
        }
        return classes;
    }
    
    
    template<class T>
    ics::ArrayMap<T,int> ArrayEquivalence<T>::heights () const {
        //Compute the depth of every node by tracing a path to its root;
        //  update the answer/height of the root if it is larger
        ics::ArrayMap<T,int> answer;
        for (auto np : parent) {
            T e = np.first;
            int depth = 0;
            while (parent[e] != e) {
                e = parent[e];
                depth++;
            }
            if ( answer[e] < depth)
                answer[e] = depth;
        }
        return answer;
    }
    
    
    template<class T>
    void ArrayEquivalence<T>::show_equivalence () const {
        std::cout << "  parent map is: " << parent       << std::endl;
        std::cout << "  root_size map: " << root_size    << std::endl;
        std::cout << "  heights map:   " << heights()    << std::endl;
        std::cout << "  max height:    " << max_height() << std::endl;
    }
    
    
}

#endif /* ARRAY_EQUIVALENCE_HPP_ */
