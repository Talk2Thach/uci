#include <iostream>
#include "artifacts.h"

void read_artifacts(Artifact *artifacts, std::size_t size)
{
    unsigned int i;
    for (i=0; i < size; i++) {
        std::cin >> artifacts[i].points;
    }
    for (i=0; i < size; i++) {
        std::cin >> artifacts[i].weight;
    }
}
