//Tianya Chen #59359881
//Edward Xia  #73387315
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"


typedef ics::ArraySet<std::string>                States;
typedef ics::ArrayQueue<std::string>              InputsQueue;
typedef ics::ArrayMap<std::string,States>         InputStatesMap;

typedef ics::ArrayMap<std::string,InputStatesMap> NDFA;
typedef ics::pair<std::string,InputStatesMap>     NDFAEntry;
typedef ics::ArrayPriorityQueue<NDFAEntry>        NDFAPQ;

typedef ics::pair<std::string,States>             Transitions;
typedef ics::ArrayQueue<Transitions>              TransitionsQueue;


//Read an open file describing the non-deterministic finite automaton (each
//  line starts with a state name followed by pairs of transitions from that
//  state: (input followed by a new state) all separated by semicolons), and
//  return a Map whose keys are states and whose associated values are another
//  Map with each input in that state (keys) and the resulting set of states it
//  can lead to.
const NDFA read_ndfa(std::ifstream &file) {
    NDFA result;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> v = ics::split(line, ";");
        if (v.size() > 1) {
            for (auto &i = ++v.begin(); i != v.end(); ++i) {
                std::string input = *i;
                result[v[0]][input].insert(*++i);
            }
        } else {
            result[v[0]] = InputStatesMap();
        }
    }
    return result;
}


//Print a label and all the entries in the finite automaton Map, in
//  alphabetical order of the states: each line has a state, the text
//  "transition:" and the Map of its transitions.
void print_ndfa(const NDFA& ndfa) {
    std::cout << "Non_Deterministic Finite Automaton Description" << std::endl;
    ics::ArrayPriorityQueue<NDFAEntry> pq(ndfa.ibegin(), ndfa.iend(), [](const NDFAEntry &a, const NDFAEntry &b){ return a.first < b.first; });
    for (auto &kv : pq) {
        std::cout << "  " << kv.first << " transitions: " << kv.second << std::endl;
    }
}


//Return a queue of the calculated transition pairs, based on the non-deterministic
//  finite automaton, initial state, and queue of inputs; each pair in the returned
//  queue is of the form: input, set of new states.
//The first pair contains "" as the input and the initial state.
//If any input i is illegal (does not lead to any state in the non-deterministic finite
//  automaton, ignore it).

TransitionsQueue process(const NDFA& ndfa, std::string state, const InputsQueue& inputs) {
    TransitionsQueue result;
    States states;
    states.insert(state);
    result.enqueue({"", states});
    for (auto &i : inputs) {
        States new_states;
        for (auto &s : states) {
            if (ndfa.has_key(s) && ndfa[s].has_key(i)) {
                new_states.insert(ndfa[s][i].ibegin(), ndfa[s][i].iend());
            }
        }
        states = new_states;
        result.enqueue({i, states});
    }
    return result;
}


//Print a TransitionsQueue (the result of calling process) in a nice form.
//Print the Start state on the first line; then print each input and the
//  resulting new states indented on subsequent lines; on the last line, print
//  the Stop state.
void interpret(TransitionsQueue& tq) {  //or TransitionsQueue or TransitionsQueue&&
	std::stringstream ss;
	Transitions start_state = tq.dequeue();
	ss << *start_state.second.ibegin();
	for (auto &pair : tq){
		ss << ";" <<pair.first;
	}
    std::cout<< "Starting new simulation with description: " << ss.str() <<std::endl;
	std::cout << "Start state = " << start_state.second << std::endl;
    Transitions t;
    while (!tq.empty()) {
        t = tq.dequeue();
        std::cout << "  Input = " << t.first << "; " << "new state = " << t.second << std::endl;
    }
    std::cout << "Stop state(s) = " << t.second << std::endl;
}



//Prompt the user for a file, create a finite automaton Map, and print it.
//Prompt the user for a file containing any number of simulation descriptions
//  for the finite automaton to process, one description per line; each
//  description contains a start state followed by inputs, all separated by
//  semicolons.
//Repeatedly read a description, print that description, put each input in a
//  Queue, process the Queue and print the results in a nice form.
int main() {
  try {
      std::ifstream file;
      ics::safe_open(file, "Enter file name of Non-Determinstic Finite Automaton", "ndfaendin01.txt");
      NDFA ndfa = read_ndfa(file);
      file.close();
      print_ndfa(ndfa);
      std::cout<<std::endl;
      ics::safe_open(file, "Enter file name of start-states and input", "ndfainputendin01.txt");
      std::cout<<std::endl;
      std::string line;
      while (std::getline(file, line)) {
          std::vector<std::string> v = ics::split(line, ";");
          InputsQueue inputs;
          for (auto &i = ++v.begin(); i != v.end(); ++i) {
              inputs.enqueue(*i);
          }
          TransitionsQueue tq = process(ndfa, v[0], inputs);
          interpret(tq);
          std::cout<<std::endl;
      }
      file.close();
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
