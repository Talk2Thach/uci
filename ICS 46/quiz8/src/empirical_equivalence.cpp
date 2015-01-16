#include <string>
#include <iostream>
#include <fstream>
#include "set.hpp"
#include "ics46goody.hpp"
#include "stopwatch.hpp"
#include "ics_exceptions.hpp"
#include <string>                    // std::hash<std::string>
#include <random>
#include "array_set.hpp"
#include "hash_equivalence.hpp"

static int hash_int(const int& i) {std::hash<int> int_hash; return (int)int_hash(i);}

int main() {
    int N            = 200000;
    int test_times   = 1;
    int merge_factor = 1;
    
    //Show as errors in Eclipse, but code will run
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,N-1);   //0 - 999,999: up to 6 digits
    try {
        std::cout << "Add/Merge Classes randomly" << std::endl;
        double total_time = 0;
        for (int count=0; count<test_times; ++count) {
            ics::HashEquivalence<int> e(hash_int);
            for (int i=0; i<N; ++i)
                e.add_singleton(i);
            
            ics::Stopwatch watch;
            watch.start();
            //while (e.numberOfClasses() != 1) {  // Alternative loop: until 1 class
            for (int i=0; i<merge_factor*N; ++i) {
                int m1 = distribution(generator);
                int m2 = distribution(generator);
                //std::cout << e.classes() << " merging: " << m1 << "/" << m2 << std::endl;
                if (!e.in_same_class(m1, m2))
                    e.merge_classes_of(m1, m2);
            }
            watch.stop();
            total_time += watch.read();
            std::cout << "\n  # of values (should be " << N << ") = " << e.size() << std::endl;
            std::cout << "  # of classes = " << e.class_count() << std::endl;
            e.show_equivalence();
        }
        
        std::cout << "\nAverage time = " << total_time/test_times << std::endl;
    } catch (ics::IcsError& e) {
        std::cout << "  " << e.what() << std::endl;
    }
}

