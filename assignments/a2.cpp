#include <iostream>
#include <iomanip>
#include <cstdio>
#include <tuple>

auto get_user_input() {
  char units;
  printf("Select your units. M: Miles, K: Kilometers: [M/K]: ");
  std::cin >> units;

  units = toupper(units);

  double distance;
  printf("Enter your trip distance: ");
  std::cin >> distance;

  // TODO: Cannot compare doubles in this way, must find other way of comparison
  if (distance < 0) {
    puts("Error: Your input was invalid.");
    puts("Distance cannot be negative.");
    exit(-1);
  }

  double speed;
  printf("Enter your vehicle's speed in kilometers per minute (km/m): ");
  std::cin >> speed;

  if (speed < 0) {
    puts("Error: Your input was invalid.");
    puts("Speed cannot be negative.");
    exit(-2);
  }
  return std::make_tuple(units, distance, speed);
}


// Convert miles to kilometers 
double mi_to_km(double miles) {
  return miles * 1.6;
}

double to_km(char units, double distance) {
  return (units == 'M') ? mi_to_km(distance) : distance;
  //double km = (units == 'M') ? distance : mi_to_km(distance);
  //return km;

  //return units == 'M' ? mi_to_km(distance) : distance;
  //return ((toupper(units) == 'M') ? mi_to_km(distance) : distance);
  //switch(toupper(units)) {
    //case 'M': distance = mi_to_km(distance); break;
  //}
}

//int calc_time(double distance, double speed) {
double calc_time(double distance, double speed) {
  return distance / speed;
  //return distance * speed;
}

// Show the trip and transportation information
//void show_trip(double km, double speed, int eta) {
void show_trip(double km, double speed, double eta) {
  // Set decimal number formatting
  //std::cout << std::fixed << std::showpoint << std::setprecision(3);
  //std::cout << "Your final destination is " << ":" << km << " kilometers away.\n";
  //std::cout << "Your estimated time of arrival for your trip is " << ":" << time << " minutes.\n";
  //std::cout << "For your vehicle traveling " << ":"  << speed << " kilometers/minute.\n";

  puts("\nTrip Stats:");
  printf("\tYour final destination is %.3f km away.\n", km);
  //printf("\tYour estimated time of arrival is %d minutes.\n", eta);
  printf("\tYour estimated time of arrival is %.f minutes.\n", eta);
  printf("\tYour vehicle is traveling at %.3f km/min.\n", speed);
}

int main() {
  auto [units, distance, speed] = get_user_input();
  

  // Convert distance to kilometers if miles are given
  double km = to_km(units, distance);

  std::cout << units << distance << speed;

  // Calculate the estimated time of arrival for the trip
  double eta = calc_time(km, speed);
  
  show_trip(km, speed, eta);
  return 0;
}
