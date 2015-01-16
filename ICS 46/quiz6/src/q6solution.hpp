//Edward Xia  UID=149235
#ifndef Q6SOLUTION_HPP_
#define Q6SOLUTION_HPP_


#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <algorithm>                 // use std::swap
#include "ics46goody.hpp"
#include "array_queue.hpp"


////////////////////////////////////////////////////////////////////////////////

//Problem #1

template<class T>
class LN {
  public:
    LN ()
      : value(), next()
    {}

    LN (const LN<T>& l)
      : value(l.value), next(l.next)
    {}

    LN (T value, LN* n = nullptr)
      : value(value), next(n)
    {}

  T   value;
  LN* next;
};


template<class T>
void selection_sort(LN<T>* l) {
    for (LN<T>* to_change = l; to_change != nullptr ; to_change = to_change->next) {
        LN<T> *min_node = to_change;
        for (LN<T>* node = to_change->next; node != nullptr; node = node->next) {
            if (node->value < min_node->value) {
                min_node = node;
            }
        }
        std::swap(to_change->value, min_node->value);
    }
}


////////////////////////////////////////////////////////////////////////////////

//Problem #2


//Precondition : Array values with indexes left_low  to left_high  are sorted
//Precondition : Array values with indexes right_low to right_high are sorted
//Note that left_high+1 = right_low (I pass both to make the code a bit simpler)
//Postcondition: Array values with indexes left_low  to right_high are sorted
//Hint: Merge into a temporary array (declared to be just big enough to store
//  all the needed values) and then copy that temporary array back into
//  the parameter array (between left_low to right_high inclusively)
//See the quiz for pseudocode for this method

void merge(int a[], int left_low,  int left_high,
                    int right_low, int right_high) {
    int size = right_high - left_low + 1;
    int sorted[size];
    
    for (int i = 0, left_i = left_low, right_i = right_low; i < size; ++i) {
        if (left_i > left_high) {
            sorted[i] = a[right_i++];
        } else if (right_i > right_high) {
            sorted[i] = a[left_i++];
        } else {
            sorted[i] = a[left_i] <= a[right_i] ? a[left_i++] : a[right_i++];
        }
    }
    for (int i = 0, j = left_low; i < size; ++i, ++j) {
        a[j] = sorted[i];
    }
}


////////////////////////////////////////////////////////////////////////////////

//Problem #3

int select_digit (int number, int place)
{return number/place % 10;}


void radix_sort(int a[], int length) {
    ics::ArrayQueue<int> sorted[10];
    for (int place = 1; place <= 1000000; place *= 10) {
        for (int i = 0; i < length; ++i) {
            sorted[select_digit(a[i], place)].enqueue(a[i]);
        }
        for (int i = 0, j = 0; i < 10; ++i) {
            while (sorted[i].size() > 0) {
                a[j++] = sorted[i].dequeue();
            }
        }
    }
}

#endif /* Q6SOLUTION_HPP_ */
