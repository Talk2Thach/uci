#include <cmath>
#include "location.hpp"

Location::Location() {
  char _;
  std::cin >> latitude_ >> _ >> latitude_direction_ >> longitude_ >> _ >> longitude_direction_;
  std::cin.ignore();
  std::getline(std::cin, name_);
};

void Location::set_latitude(double latitude) {
  latitude_ = latitude;
}
double Location::latitude() const {
  return latitude_;
}

void Location::set_latitude_direction(char latitude_direction) {
  latitude_direction_ = latitude_direction;
}
char Location::latitude_direction() const {
  return latitude_direction_;
}

void Location::set_longitude(double longitude) {
  longitude_ = longitude;
}
double Location::longitude() const {
  return longitude_;
}

void Location::set_longitude_direction(char longitude_direction) {
  longitude_direction_ = longitude_direction;
}
char Location::longitude_direction() const {
  return longitude_direction_;
}

void Location::set_name(std::string name) {
  name_ = name;
}
std::string Location::name() const {
  return name_;
}

double Location::distance_to(Location *location) {
  double R = 3959.9;
  double delta_latitude, delta_longitude, a, c;
  delta_latitude = this->signed_latitude_in_radian() - location->signed_latitude_in_radian();
  delta_longitude = this->signed_longitude_in_radian() - location->signed_longitude_in_radian();
  a = pow(sin(delta_latitude / 2.), 2) + cos(this->signed_latitude_in_radian()) * cos(location->signed_latitude_in_radian()) * pow(sin(delta_longitude / 2.), 2);
  c = 2 * atan2(sqrt(a), sqrt(1 - a));
  return R * c;
}

double Location::signed_latitude_in_radian() const {
  if (latitude_direction_ == 'N') {
    return latitude_ * M_PI / 180.;
  } else {
    return -latitude_ * M_PI / 180.;
  }
};

double Location::signed_longitude_in_radian() const {
  if (longitude_direction_ == 'E') {
    return longitude_ * M_PI / 180.;
  } else {
    return -longitude_ * M_PI / 180.;
  }
};

std::ostream& operator << (std::ostream& os, const Location *location) {
  return os << location->latitude() << "/" << location->latitude_direction() << " " << location->longitude() << "/" << location->longitude_direction() << " (" << location->name() << ")";
}
