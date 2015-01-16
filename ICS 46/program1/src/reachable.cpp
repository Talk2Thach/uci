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


typedef ics::ArraySet<std::string>           NodeSet;
typedef ics::pair<std::string,NodeSet>       GraphEntry;
typedef ics::ArrayPriorityQueue<GraphEntry>  GraphPQ;
typedef ics::ArrayMap<std::string,NodeSet>   Graph;


//Read an open file of edges (node names separated by semicolons, with an
//  edge going from the first node name to the second node name) and return a
//  Graph (Map) of each node name associated with the Set of all node names to
//  which there is an edge from the key node name.
Graph read_graph(std::ifstream &file) {
    Graph result;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> edge = ics::split(line, ";");
        result[edge[0]].insert(edge[1]);
    }
    return result;
}


//Print a label and all the entries in the Graph, in alphabetical order.
//Use a "->" to separate the key node name from the Set of node names to
//  which it has an edge.
void print_graph(const Graph& graph) {
    std::cout << "Graph: source -> {destination} edges" << std::endl;
    GraphPQ pq(graph.ibegin(), graph.iend(), [](const GraphEntry &a, const GraphEntry &b){ return a.first < b.first; });
    for (auto &kv : pq) {
        std::cout << "  " << kv.first << " -> " << kv.second << std::endl;
    }
}


//Return the Set of node names reaching in the Graph starting at the
//  specified (start) node.
//Use a local Set and a Queue to respectively store the reachable nodes and
//  the nodes that are being explored.
NodeSet reachable(const Graph& graph, std::string start) {
    NodeSet result;
    if (graph.has_key(start)) {
        ics::ArrayQueue<std::string> exploring;
        exploring.enqueue(start);
        while (!exploring.empty()) {
            start = exploring.dequeue();
            result.insert(start);
            if (graph.has_key(start)) {
                for (auto &sub_node : graph[start]) {
                    if (!result.contains(sub_node)) {
                        exploring.enqueue(sub_node);
                    }
                }
            }
        }
    }
    return result;
}



//Prompt the user for a file, create a graph from its edges, print the graph,
//  and then repeatedly (until the user enters "quit") prompt the user for a
//  starting node name and then either print an error (if that the node name
//  is not a source node in the graph) or print the Set of node names
//  reachable from it using the edges in the Graph.
int main() {
  try {
      std::ifstream file;
      ics::safe_open(file, "Enter graph file name", "graph1.txt");
      std::cout << std::endl;
      Graph graph = read_graph(file);
      file.close();
      print_graph(graph);
      std::cout << std::endl;
      std::string start;
      while ( (start = ics::prompt_string("Enter starting node (enter quit to quit)")) != "quit" ) {
          NodeSet result = reachable(graph, start);
          if (result.size() > 0) {
              std::cout << "Reachable from node name " << start << " = " << result << std::endl;
          } else {
              std::cout << "  " << start << " is not a source node name in the graph" << std::endl;
          }
          std::cout << std::endl;
      }
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
