#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "array_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"



template<class KEY,class T>
void swap (ics::ArrayMap<KEY,T>& m, KEY key1, KEY key2) {
	m.put(key1, m.put(key2, m[key1]));
}


template<class KEY,class T>
void values_set_to_queue (const ics::ArrayMap<KEY,ics::ArraySet<T>>& m1,
                          ics::ArrayMap<KEY,ics::ArrayQueue<T>>& m2) {
	for (auto &i : m1)
		m2[i.first].enqueue(i.second.ibegin(), i.second.iend());
}


template<class KEY>
ics::ArraySet<KEY> reachable (const ics::ArrayMap<KEY,KEY>& m, KEY k) {
	ics::ArraySet<KEY> s;
	while (s.insert(k))
		k = m[k];
	return s;
}


template<class T>
ics::ArrayMap<T,ics::ArraySet<T>> follows (const ics::ArrayQueue<T>& q) {
	ics::ArrayMap<T,ics::ArraySet<T>> m;
	auto &i = q.ibegin();
	T key = *i++;
	while (i != q.iend()) {
		m[key].insert(*i);
		key = *i++;
	}
	return m;
}


template<class T>
ics::ArrayMap<T,ics::ArraySet<T>> reverse (const ics::ArrayMap<T,ics::ArraySet<T>>& m) {
	ics::ArrayMap<T,ics::ArraySet<T>> r;
	for (auto &i : m)
		for (auto &j : i.second)
			r[j].insert(i.first);
	return r;
}

#endif /* SOLUTION_HPP_ */


