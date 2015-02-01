#include <iostream>
#include "location.hpp"

int main(int argc, char *argv[])
{
  int size;
  double distance, closest_distance, farthest_distance;

  Location *start_location, *closest_location, *farthest_location, *location;
  start_location = new Location();
  std::cin >> size;
  if (size > 0) {
    for (int i = 0; i < size; i++) {
      location = new Location();
      distance = start_location->distance_to(location);
      if (i == 0) {
        closest_distance = distance;
        closest_location = location;
        farthest_distance = distance;
        farthest_location = location;
      } else if (distance < closest_distance) {
        if (closest_location != farthest_location) {
          delete closest_location;
        }
        closest_distance = distance;
        closest_location = location;
      } else if (distance > farthest_distance) {
        if (farthest_location != closest_location) {
          delete farthest_location;
        }
        farthest_distance = distance;
        farthest_location = location;
      } else {
        delete location;
      }
    }
    std::cout << "Start Location: " << start_location << std::endl;
    std::cout << "Closest Location: " << closest_location << " (" << closest_distance << " miles)" << std::endl;
    std::cout << "Farthest Location: " << farthest_location << " (" << farthest_distance << " miles)" << std::endl;
    delete closest_location;
    delete farthest_location;
  }
  delete start_location;
  return 0;
}

