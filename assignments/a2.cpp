/**
  * Student Name    : Joseph Diza
  * Student Number  : 100427500
  * Course Name     : INFO 1112 S10
  **/
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

// Generic input validation
const char* ERROR_INVALID_INPUT = "Error: Your input was invalid. Please try again.";
const std::vector<std::string> valid_yes_or_no_inputs { "Yes", "yes", "No", "no" };

// Prompts user for input, for any input type
template <typename T>
T prompt(const char* msg) {
  T input;
  printf("%s", msg);
  std::cin >> input;
  return input;
}

// Returns true if the input was valid, and false otherwise, for any input type
template <typename T>
bool is_valid(std::vector<T> valid_inputs, T input) {
  for (auto valid_input : valid_inputs)
    if (input == valid_input)
      return true;
  return false;
}

// Accepts only valid inputs types, for any input data type
template <typename T>
T accept_only_valid_inputs(
    const char* msg,
    const char* error_prompt,
    std::vector<T> valid_inputs) {
  // Get user input
  T input = prompt<T>(msg);

  bool input_is_valid = is_valid<T>(valid_inputs, input);

  // If input is invalid
  while (!input_is_valid) {
    // Display the error message
    //printf("%s\n", error_prompt);
    puts(error_prompt);

    // Force user to give valid input
    input = prompt<T>(msg);

    // Check if the new input is valid
    input_is_valid = is_valid<T>(valid_inputs, input);
  }
  return input;
}

// Get valid user input
auto get_user_input() {
  char units = accept_only_valid_inputs<char>("Select your units. M: Miles, K: Kilometers: [M/K]: ", ERROR_INVALID_INPUT, {'M', 'K', 'm', 'k'});
  units = toupper(units);

  // Reduce code duplication with specific lambda function
  auto accept_only_positive_numbers = [](const char* msg, const char* data) -> double {
    // Accept only positive decimal numbers, and force user to retry if negative value is entered
    double number = prompt<double>(msg);
    while (number < 0) {
      printf("Error: Your input was invalid. %s cannot be negative. Please try again.\n", data);
      number = prompt<double>(msg);
    }
    return number;
  };

  double distance = accept_only_positive_numbers("Enter your trip distance: " , "Distance");
  double speed = accept_only_positive_numbers("Enter your vehicle's speed in kilometers per minute (km/m): ", "Speed");
  
  puts(""); // Print empty line
  return std::make_tuple(units, distance, speed);
}

// Road Trip Functions
// Convert miles to kilometers 
double mi_to_km(double miles) {
  return miles * 1.6;
}

// Converts miles to kilometers if they units are in miles, else returns the distance parameter
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

  std::string oil_level_prompt = "What is the oil level indicated by your vehicle's dipstick?\n"
    "\t0: Below minimum\n"
    "\t1: Between minimum and maximum\n"
    "\t2: Above maximum\n"
    "[0, 1, 2]: ";

  int oil_level = accept_only_valid_inputs<int>(oil_level_prompt.c_str(), ERROR_INVALID_INPUT, { 0, 1, 2 });

  // Lambda function that accepts only yes or no inputs, and reduces code duplication
  auto accept_only_yes_or_no = [&] (const char* prompt) -> std::string
    { return accept_only_valid_inputs<std::string>(prompt, ERROR_INVALID_INPUT, valid_yes_or_no_inputs); };

  std::string tire_pressure = accept_only_yes_or_no("Are your front and rear tire pressures between 30 and 35 psi? Answer [Yes/No]: ");
  std::string engine_temp_light = accept_only_yes_or_no("Is your engine temperature warning light on? Answer [Yes/No]: ");
  std::string battery_alert_light = accept_only_yes_or_no("Is the battery alert light on? Answer [Yes/No]:");
  puts(""); // Print empty line

  return std::make_tuple(oil_level, tire_pressure, engine_temp_light, battery_alert_light);
}

std::vector<SafetyConcern> check_vehicle_safety(
    int oil_level,
    std::string tire_pressure,
    std::string engine_temp_light,
    std::string battery_alert_light) {

  std::vector<SafetyConcern> safety_concerns;
  // List of all possible safety concerns:
  SafetyConcern oil_leak { "Oil Level is Below Minimum", "You should inspect for any oil leaks, and add more oil as needed"};
  SafetyConcern oil_overflow { "Oil Level is Above Maximum", "You should drain the excess oil at an automotive repair shop"};
  SafetyConcern incorrect_tire_pressure { "Tire Pressure is Not Between 30-35 psi", "Check the tire pressure and inflate or deflate them as needed"};
  SafetyConcern engine_temp_light_is_on { "Engine Temperature Warning Light is On", "Call a roadside service to tow your vehicle to a repair shop"};
  SafetyConcern battery_alert_light_is_on { "Battery Alert Light is On", "You should have your electrical systems checked for faults at a repair shop. A new battery may be needed."};

  // SafetyConcern check
  if (oil_level == 0) 
    safety_concerns.push_back(oil_leak);
  else if (oil_level == 2)
    safety_concerns.push_back(oil_overflow);

  if (capitalize(tire_pressure) == "No")
    safety_concerns.push_back(incorrect_tire_pressure);

  if (capitalize(engine_temp_light) == "Yes")
    safety_concerns.push_back(engine_temp_light_is_on);

  if (capitalize(battery_alert_light) == "Yes")
    safety_concerns.push_back(battery_alert_light_is_on);

  return safety_concerns;
}

// Displays the vehicle safety condition in a formatted table
void show_vehicle_condition(std::vector<SafetyConcern> safety_concerns) {
  // Useful lambda functions for printing formatted table
  auto print_stars = []() { std::cout << std::setfill('*') << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << "*" << std::setfill(' '); };
  auto print_gaps = [] () { std::cout << std::setw(6) << " "; };
  auto print_col = [](const char* text) { std::cout << std::setw(SAFETY_CONCERN_TABLE_WIDTH) << text; };

  // If there are any safety concerns
  if (safety_concerns.size() > 0) {
    std::cout << std::left; // Left justify all column text
    // Print safety concern header
    print_col("Safety Concern");  print_gaps(); print_col("Precaution");  puts("");
    print_stars();                print_gaps(); print_stars();            puts("");
  } else {
    // Wish the user the best on their road trip
    std::cout << "Have a safe trip! Your vehicle is free of any issues or potential safety concerns.";
  }

  // Print safety concerns in formatted table
  for (auto safety_concern : safety_concerns) {
    print_col(safety_concern.concern); print_gaps(); print_col(safety_concern.precaution); puts("");
  }
  std::cout << std::right; // Reset justification
}

int main() {
  // Get trip information
  auto [units, distance, speed] = get_user_input();

  // Get vehicle condition
  auto [oil_level, tire_pressure, engine_temp_light, battery_alert_light] = get_vehicle_condition();
  
  // Convert distance to kilometers if miles are given
  double km = to_km(units, distance);

  // Calculate the estimated time of arrival for the trip
  double eta = calc_time(km, speed);
  
  // Show road trip information
  show_trip(km, speed, eta);

  // Check vehicle safety
  auto safety_concerns = check_vehicle_safety(oil_level, tire_pressure, engine_temp_light, battery_alert_light);

  // Show current vehicle safety condition
  show_vehicle_condition(safety_concerns);
  return 0;
}
