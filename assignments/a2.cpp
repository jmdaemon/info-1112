/**
  Joseph Diza
  100427500
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <tuple>

// Get valid user input
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
  puts(""); // Print empty line
  return std::make_tuple(units, distance, speed);
}

// Road Trip Functions
// Convert miles to kilometers 
double mi_to_km(double miles) {
  return miles * 1.6;
}

double to_km(char units, double distance) {
  return (units == 'M') ? mi_to_km(distance) : distance;
}

double calc_time(double distance, double speed) {
  return distance / speed;
}

// Show the trip and transportation information
void show_trip(double km, double speed, double eta) {
  puts("\nTrip Stats:");
  printf("\tYour final destination is %.3f km away.\n", km);
  printf("\tYour estimated time of arrival is %.f minutes.\n", eta);
  printf("\tYour vehicle is traveling at %.3f km/min.\n\n", speed);
}

// Road Trip Safety Functions
std::string capitalize(std::string s) {
  s[0] = toupper(s[0]);
  return s;
}

// Get valid information about user's vehicle
auto get_vehicle_condition() {
  puts("Allow us to check the safety of your vehicle. Please answer the following questions.");

  puts("What is the oil level indicated by your vehicle's dipstick?");
  puts("\t0: Below minimum");
  puts("\t1: Between minimum and maximum");
  printf("[0, 1, 2]: ");

  int oil_level;
  std::cin >> oil_level;

  std::string tire_pressure;
  printf("Are your front and rear tire pressures between 30 and 35 psi? Answer [Yes/No]: ");
  std::cin >> tire_pressure;

  std::string engine_temp_light;
  printf("Is your engine temperature warning light on? Answer [Yes/No]: ");
  std::cin >> engine_temp_light;

  std::string battery_alert_light;
  printf("Is the battery alert light on? Answer [Yes/No]: ");
  std::cin >> battery_alert_light;
  puts(""); // Print empty line

  return std::make_tuple(oil_level, tire_pressure, engine_temp_light, battery_alert_light);
}

void show_vehicle_condition(
    int oil_level,
    std::string tire_pressure,
    std::string engine_temp_light,
    std::string battery_alert_light) {

  if (oil_level == 0) {
    puts("You should inspect for any oil leaks, and add more oil as needed");
  } else if (oil_level == 2) {
    puts("You should drain the excess oil at an automotive repair shop");
  }

  if (capitalize(tire_pressure) == "No") {
    puts("Check the tire pressure and inflate or deflate them as needed");
  }

  if (capitalize(engine_temp_light) == "Yes") {
    puts("Call a roadside service to tow your vehicle to a repair shop");
  }

  if (capitalize(battery_alert_light) == "Yes") {
    puts("You should have your electrical systems checked for faults at a repair shop. A new battery may be needed.");
  }
}

int main() {
  auto [units, distance, speed] = get_user_input();

  // Get vehicle condition
  auto [oil_level, tire_pressure, engine_temp_light, battery_alert_light] = get_vehicle_condition();
  
  // Show road trip information
  // Convert distance to kilometers if miles are given
  double km = to_km(units, distance);

  // Calculate the estimated time of arrival for the trip
  double eta = calc_time(km, speed);
  
  show_trip(km, speed, eta);

  // Show current vehicle safety condition
  show_vehicle_condition(oil_level, tire_pressure, engine_temp_light, battery_alert_light);
  return 0;
}
