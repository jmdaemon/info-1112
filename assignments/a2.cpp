/**
  Joseph Diza
  100427500
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <tuple>
#include <vector>

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

// Road Trip Safety Functionality
const unsigned short SAFETY_CONCERN_TABLE_WIDTH = 40; 

struct SafetyConcern {
  const char* concern;
  const char* precaution;
};

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
  puts("\t2: Above maximum");
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

  std::vector<SafetyConcern> safety_concerns;
  //safety_concerns.push_back()
  if (oil_level == 0) {
    SafetyConcern oil_leak { "Oil Level is Below Minimum", "You should inspect for any oil leaks, and add more oil as needed"};
    safety_concerns.push_back(oil_leak);
    //puts();
  } else if (oil_level == 2) {
    SafetyConcern oil_overflow { "Oil Level is Above Maximum", "You should drain the excess oil at an automotive repair shop"};
    safety_concerns.push_back(oil_overflow);
  }

  if (capitalize(tire_pressure) == "No") {
    SafetyConcern incorrect_tire_pressure { "Tire Pressure is Not Between 30-35 psi", "Check the tire pressure and inflate or deflate them as needed"};
    safety_concerns.push_back(incorrect_tire_pressure);
  }

  if (capitalize(engine_temp_light) == "Yes") {
    SafetyConcern engine_temp_light_is_on { "Engine Temperature Warning Light is On", "Call a roadside service to tow your vehicle to a repair shop"};
    safety_concerns.push_back(engine_temp_light_is_on);
  }

  if (capitalize(battery_alert_light) == "Yes") {
    SafetyConcern battery_alert_light_is_on { "Battery Alert Light is On", "You should have your electrical systems checked for faults at a repair shop. A new battery may be needed."};
    safety_concerns.push_back(battery_alert_light_is_on);
  }

  // Useful lambda functions for printing formatted table
  auto print_stars = []() { std::cout << std::setfill('*') << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << "*" << std::setfill(' '); };
  auto print_gaps = [] () { std::cout << std::setw(6) << " "; };
  auto print_col = [](const char* text) { std::cout << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << text; };

  if (safety_concerns.size() > 0) {
    std::cout << std::left;

    print_col("Safety Concern"); print_gaps(); print_col("Precaution"); puts("");

    //std::cout <<
      //std::left <<
      //std::setw(SAFETY_CONCERN_TABLE_WIDTH) << "Safety Concern" <<
      //std::setw(6) << " " <<
      //std::setw(SAFETY_CONCERN_TABLE_WIDTH) << "Precaution" << std::endl;

    print_stars(); print_gaps(); print_stars(); puts("");
    //std::cout <<
      //std::setfill('*') << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << "*" <<
      //std::setfill(' ') << std::setw(6) << " " <<
      //std::setfill('*') << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << "*" <<
      //std::setfill(' ') << std::endl;
  } else {
    std::cout << "Have a safe trip! Your vehicle is free of any issues or potential safety concerns.";
  }
  for (auto safety_concern : safety_concerns) {
    //std::cout << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << safety_concern.concern << std::setw(6) << " " << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << safety_concern.precaution << std::endl;
    print_col(safety_concern.concern); print_gaps(); print_col(safety_concern.precaution); puts("");
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
