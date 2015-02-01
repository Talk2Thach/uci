#include <iostream>
#include <string>
#include <sstream>
#include "HashMap.hpp"

int main()
{
    bool debug = false;
    std::string line, command, email, pass;
    HashMap logins = HashMap();
    while (true) {
        std::getline(std::cin, line);
        if (line == "QUIT") {
            std::cout << "GOODBYE" << std::endl;
            break;
        } else if (line == "CLEAR") {
            logins = HashMap();
            std::cout << "CLEARED" << std::endl;
            break;
        } else if (line == "DEBUG ON") {
            if (debug) {
                std::cout << "ON ALREADY" << std::endl;
            } else {
                debug = true;
                std::cout << "ON NOW" << std::endl;
            }
        } else if (line == "DEBUG OFF") {
            if (debug) {
                debug = false;
                std::cout << "OFF NOW" << std::endl;
            } else {
                std::cout << "OFF ALREADY" << std::endl;
            }
        } else if (line == "LOGIN COUNT") {
            if (debug) {
                std::cout << logins.size() << std::endl;
            } else {
                std::cout << "INVALID" << std::endl;
            }
        } else if (line == "BUCKET COUNT") {
            if (debug) {
                std::cout << logins.bucketCount() << std::endl;
            } else {
                std::cout << "INVALID" << std::endl;
            }
        } else if (line == "LOAD FACTOR") {
            if (debug) {
                std::cout << logins.loadFactor() << std::endl;
            } else {
                std::cout << "INVALID" << std::endl;
            }
        } else if (line == "MAX BUCKET SIZE") {
            if (debug) {
                std::cout << logins.maxBucketSize() << std::endl;
            } else {
                std::cout << "INVALID" << std::endl;
            }
        } else {
            std::istringstream stream(line);
            command = "";
            email = "";
            pass = "";
            stream >> command;
            if (command == "CREATE") {
                stream >> email >> pass;
                if (email == "" || pass == "") {
                    std::cout << "INVALID" << std::endl;
                } else if (logins.contains(email)) {
                    std::cout << "EXISTS" << std::endl;
                } else {
                    logins.add(email, pass);
                    std::cout << "CREATED" << std::endl;
                }
            } else if (command == "LOGIN") {
                stream >> email >> pass;
                if (email == "" || pass == "") {
                    std::cout << "INVALID" << std::endl;
                } else if (logins.value(email) == pass) {
                    std::cout << "SUCCEEDED" << std::endl;
                } else {
                    std::cout << "FAILED" << std::endl;
                }
            } else if (command == "REMOVE") {
                stream >> email;
                if (email == "") {
                    std::cout << "INVALID" << std::endl;
                } else if (logins.contains(email)) {
                    logins.remove(email);
                    std::cout << "REMOVED" << std::endl;
                } else {
                    std::cout << "NONEXISTENT" << std::endl;
                }
            } else {
                std::cout << "INVALID" << std::endl;
            }
        }
    }
    return 0;
}
