#include <iostream>
#include <string>
#include <tuple>

#include <cstdio>


auto get_user_input() {
  std::string units;
  printf("Select your units. M: Miles, K: Kilometers: [M/K]: ");
  std::cin >> units;

  double distance;
  printf("Enter your trip distance: ");
  std::cin >> distance;

  double speed;
  printf("Enter your vehicle's speed in kilometers per minute (km/m): ");
  std::cin >> speed;
}

// Check car for potential safety concerns
// Validates inputs
//auto check_car() {
//auto get_vehicle_safety_input() {

//bool string_contains_yes_or_no(std::string s) {
  ////s = tolower(s);
  //return (s == "Yes" || s == "No");
//}

// Accepts only the valid inputs given in the array
// True means that a valid input was found
// False indicates that a valid input was not given
bool accept_only(std::string valid_inputs[], std::string input) {
  //for (std::string valid_input : valid_inputs) {
    //if (input == valid_input)
      //return true;
    //}
  //}
  for (auto it = valid_inputs->begin(); it != valid_inputs->end(); ++it) {
    if (input == it.base())
      return true;
  }
  return false;
}

// A loop that only allows the valid inputs to be given
// Displays an error message if an invalid input was given
std::string accept_only_valid(const char* prompt, const char* error_prompt, std::string valid_inputs[], std::string input) {
  bool input_is_valid = accept_only(valid_inputs, input);
  std::string result = input;
  while (!input_is_valid) {
    // Display the error message
    printf("%s", error_prompt);

    // Get another input
    printf("%s", prompt);
    std::cin >> input;

    // Check if the input is valid
    input_is_valid = accept_only(valid_inputs, input);
  }
}

auto get_vehicle_condition() {
  printf("Allow us to check the safety of your vehicle. Please answer the following questions.");
  const char* invalid_input = "Error: Your input was invalid.";

  std::string oil_level_prompt = "What is the oil level indicated by your vehicle's dipstick?";
  oil_level_prompt += "\t0: Below minimum";
  oil_level_prompt += "\t1: Between minimum and maximum";
  oil_level_prompt += "\t2: Above maximum\n";
  oil_level_prompt += "[0, 1, 2]: ";

  //int oil_level;
  //printf("What is the oil level indicated by your vehicle's dipstick?");
  //puts("\t0: Below minimum");
  //puts("\t1: Between minimum and maximum");
  //puts("\t2: Above maximum");
  //printf("[0, 1, 2]: ");
  //std::cin >> oil_level;

  int oil_level = atof(accept_only_valid(oil_level_prompt.c_str(), invalid_input).c_str());

  std::string tire_pressure;
  printf("Are your front and rear tire pressures between 30 and 35 psi? Answer [Yes/No]: ");
  std::cin >> tire_pressure;

  std::string engine_temp_light;
  printf("Is your engine temperature warning light on? Answer [Yes/No]: ");
  std::cin >> engine_temp_light;

  std::string battery_alert_light;
  printf("Is the battery alert light on? Answer [Yes/No]:");
  
  return std::make_tuple(oil_level, tire_pressure, engine_temp_light, battery_alert_light);
}

int main () {
  get_vehicle_condition();
  return 0;
}
