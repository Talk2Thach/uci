#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "hash_graph.hpp"
#include "dijkstra.hpp"


std::string get_node_in_graph(const ics::HashGraph<int>& g, std::string prompt, bool allow_QUIT) {
    std::string node;
    for(;;) {
        node = ics::prompt_string(prompt + " (must be in graph" + (allow_QUIT ? " or QUIT" : "") + ")");
        if ((allow_QUIT && node == "QUIT") || g.has_node(node))
            break;
    }
    return node;
}


int main() {
    try {
        std::ifstream file;
        ics::safe_open(file, "Enter graph file name", "flightcost.txt");
        ics::HashGraph<int> graph;
        graph.load(file, ";");
        std::cout << graph << std::endl;
        std::string start = get_node_in_graph(graph, "Enter start node", false);
        ics::HashMap<std::string,ics::Info> dijkstra_map = ics::extended_dijkstra(graph, start);
        std::cout << dijkstra_map << std::endl << std::endl;
        std::string end;
        while ( (end = get_node_in_graph(graph, "Enter stop node", true)) != "QUIT" ) {
            std::cout << "Cost is " << dijkstra_map[end].cost << "; path is " << ics::recover_path(dijkstra_map, end) << std::endl << std::endl;
        }
    } catch (ics::IcsError& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
