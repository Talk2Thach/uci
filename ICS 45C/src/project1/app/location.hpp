#include <string>
#include <iostream>

class Location {
 public:
  Location();
  void set_latitude(double latitude);
  double latitude() const;
  void set_latitude_direction(char latitude_direction);
  char latitude_direction() const;
  void set_longitude(double longitude);
  double longitude() const;
  void set_longitude_direction(char longitude_direction);
  char longitude_direction() const;
  void set_name(std::string name);
  std::string name() const;
  double distance_to(Location *location);

 private:
  double latitude_, longitude_;
  char latitude_direction_, longitude_direction_;
  std::string name_;

  double signed_latitude_in_radian() const;
  double signed_longitude_in_radian() const;
};
std::ostream& operator << (std::ostream& os, const Location *location);
