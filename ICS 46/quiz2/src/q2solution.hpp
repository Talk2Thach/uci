#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include <string>
#include <iostream>
#include <fstream>


template<class T>
class LN {
  public:
    LN ()                        : next(nullptr){}
    LN (const LN<T>& ln)         : value(ln.value), next(ln.next){}
    LN (T v, LN<T>* n = nullptr) : value(v), next(n){}
    T      value;
    LN<T>* next;
};


template<class T>
std::ostream& operator << (std::ostream& outs, LN<T>* l) {
  for (LN<T>* p = l; p != nullptr; p = p->next)
    std::cout << p->value << "->";
  std::cout << "nullptr";
  return outs;
}



char relation (const std::string& s1, const std::string& s2) {
    if (s1 == "" && s2 == "")
        return '=';
    if (s1 == "" || s1[0] < s2[0])
        return '<';
    if (s2 == "" || s1[0] > s2[0])
        return '>';
    return relation(s1.substr(1, std::string::npos), s2.substr(1, std::string::npos));
}


template<class T>
void add_ordered_i (LN<T>*& l, T value) {
    if (l == nullptr || value < l->value) {
        l = new LN<T>(value, l);
    } else {
        LN<T> *n = l;
        while (n->next != nullptr && value > n->next->value)
            n = n->next;
        n->next = new LN<T>(value, n->next);
    }
}


template<class T>
void add_ordered_r (LN<T>*& l, T value) {
    if (l == nullptr || value < l->value)
        l = new LN<T>(value, l);
    else
        add_ordered_i(l->next, value);
}



#endif /* SOLUTION_HPP_ */
