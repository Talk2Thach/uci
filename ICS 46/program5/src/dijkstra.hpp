#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
#include "array_stack.hpp"
#include "hash_graph.hpp"

namespace ics {
    
    
    int hash(const std::string& s) {std::hash<std::string> str_hash; return (int)str_hash(s);}
    
    
    class Info {
    public:
        Info(){}
        int          cost     = std::numeric_limits<int>::max();
        std::string from      = "?";
        bool operator == (const Info& rhs) const {
            return cost == rhs.cost && from == rhs.from;
        }
        bool operator != (const Info& rhs) const {
            return !(*this == rhs);
        }
        friend std::ostream& operator << (std::ostream& outs, const Info& i) {
            outs << "Info[" << i.cost << "," << i.from << "]";
            return outs;
        }
        
    };
    
    
    //Return the final_map as specified in the description of extended Dijkstra algorithm
    ics::HashMap<std::string,Info> extended_dijkstra(const ics::HashGraph<int>& g, std::string start_node) {
        ics::HashMap<std::string,Info> info_map(hash);
        ics::HashMap<std::string,Info> answer_map(hash);

        for (auto &node : g.all_nodes()) {
            info_map[node.first] = Info();
        }
        std::string min_from = start_node;
        info_map[min_from].cost = 0;
        
        while (!info_map.empty()) {
            int min_cost = std::numeric_limits<int>::max();
            for (auto &info_pair : info_map) {
                if (info_pair.second.cost < min_cost) {
                    min_cost = info_pair.second.cost;
                    min_from = info_pair.first;
                }
            }
            if (min_cost == std::numeric_limits<int>::max()) {
                break;
            }
            answer_map[min_from] = info_map.erase(min_from);
            for (auto &out_node : g.all_nodes()[min_from].out_nodes) {
                if (!answer_map.has_key(out_node)) {
                    int cost = answer_map[min_from].cost + g.edge_value(min_from, out_node);
                    if (cost < info_map[out_node].cost) {
                        info_map[out_node].cost = cost;
                        info_map[out_node].from = min_from;
                    }
                }
            }
        }
        return answer_map;
    }
    
    
    //Return a string from the start node (implicit in answer_map) to the end node
    //  (left to right, separated by a space)
    std::string recover_path(ics::HashMap<std::string,Info> answer_map, std::string end_node) {
        ArrayStack<std::string> reverse_path;
        for (std::string node = end_node; node != "?" ; node = answer_map[node].from) {
            reverse_path.push(node);
        }
        std::ostringstream oss;
        oss << reverse_path.pop();
        while (!reverse_path.empty()) {
            oss << " " << reverse_path.pop();
        }
        return oss.str();
    }
    
    
}

#endif /* DIJKSTRA_HPP_ */
