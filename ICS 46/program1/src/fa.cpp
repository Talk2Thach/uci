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


typedef ics::ArrayQueue<std::string>             InputsQueue;
typedef ics::ArrayMap<std::string,std::string>   InputStateMap;

typedef ics::ArrayMap<std::string,InputStateMap> FA;
typedef ics::pair<std::string,InputStateMap>     FAEntry;
typedef ics::ArrayPriorityQueue<FAEntry>         FAPQ;

typedef ics::pair<std::string,std::string>       Transition;
typedef ics::ArrayQueue<Transition>              TransitionQueue;


//Read an open file describing the finite automaton (each line starts with
//  a state name followed by pairs of transitions from that state: (input
//  followed by new state) all separated by semicolons), and return a Map
//  whose keys are states and whose associated values are another Map with
//  each input in that state (keys) and the resulting state it leads to.
const FA read_fa(std::ifstream &file) {
    FA result;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> v = ics::split(line, ";");
        for (auto &i = ++v.begin(); i != v.end(); ++i) {
            std::string input = *i;
            result[v[0]][input] = *++i;

        }
    }
    return result;
}


//Print a label and all the entries in the finite automaton Map, in
//  alphabetical order of the states: each line has a state, the text
//  "transition:" and the Map of its transitions.
void print_fa(const FA& fa) {
    std::cout << "Finite Automaton Description" << std::endl;
    for (auto &kv : fa) {
        std::cout << "  " << kv.first << " transitions: " << kv.second << std::endl;
    }
}


//Return a queue of the calculated transition pairs, based on the finite
//  automaton, initial state, and queue of inputs; each pair in the returned
//  queue is of the form: input, new state.
//The first pair contains "" as the input and the initial state.
//If any input i is illegal (does not lead to a state in the finite
//  automaton, then the last pair in the returned queue is i,"None".
TransitionQueue process(const FA& fa, std::string state, const InputsQueue& inputs) {
    TransitionQueue result;
    result.enqueue({"",state});
    for (auto &i : inputs) {
        try {
            state = fa[state][i];
        } catch (ics::KeyError e) {
            result.enqueue({i,"None"});
            break;
        }
        result.enqueue({i,state});
    }
    return result;
}


//Print a TransitionQueue (the result of calling process) in a nice form.
//Print the Start state on the first line; then print each input and the
//  resulting new state (or "illegal input: terminated", if the state is
//  "None") indented on subsequent lines; on the last line, print the Stop
//  state (which might be "None").
void interpret(TransitionQueue& tq) {  //or TransitionQueue or TransitionQueue&&
    std::cout << "Start state = " << tq.dequeue().second << std::endl;
    Transition t;
    while (!tq.empty()) {
        t = tq.dequeue();
        std::cout << "  Input = " << t.first << "; ";
        if (t.second == "None") {
            std::cout << "illegal input: terminated";
        } else {
            std::cout << "new state = " << t.second;
        }
        std::cout << std::endl;
    }
    std::cout << "Stop state = " << t.second << std::endl;
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
      ics::safe_open(file, "Enter file with finite automaton", "faparity.txt");
      std::cout << std::endl;
      FA fa = read_fa(file);
      file.close();
      print_fa(fa);
      std::cout << std::endl;
      ics::safe_open(file, "Enter file with start-state and input", "fainputparity.txt");
      std::cout << std::endl;
      std::string line;
      while (std::getline(file, line)) {
          std::vector<std::string> v = ics::split(line, ";");
          InputsQueue inputs;
          for (auto &i = ++v.begin(); i != v.end(); ++i) {
              inputs.enqueue(*i);
          }
          std::cout << "Starting new simulation with description: " << line << std::endl;
          TransitionQueue tq = process(fa, v[0], inputs);
          interpret(tq);
          std::cout << std::endl;
      }
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
