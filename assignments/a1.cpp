/**
  Joseph Diza
  100427500
*/
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include <cstdio>

/** Library Types & Constants **/
const char* ERROR_INVALID_INPUT = "Error: Your input was invalid.";
typedef std::vector<std::string> ValidInput;

/** Library Functions **/

/** Prompts a user for input, and returns the input **/
std::string prompt(const char* msg) {
  std::string input;
  printf("%s", msg);
  std::cin >> input;
  return input;
}

/** Returns true if the input was valid, and false otherwise **/
bool accept_only(ValidInput valid_inputs, std::string input) {
  for (auto valid_input : valid_inputs)
    if (input == valid_input)
      return true;
  return false;
}

/** Continually prompts for an input until a valid input is given **/
std::string accept_only_valid_inputs(const char* msg, const char* error_prompt, ValidInput valid_inputs) {
  // Get user input
  std::string input = prompt(msg);

  bool input_is_valid = accept_only(valid_inputs, input);

  // If input is invalid
  while (!input_is_valid) {
    // Display the error message
    printf("%s\n", error_prompt);

    // Force user to give valid input
    input = prompt(msg);

    // Check if the new input is valid
    input_is_valid = accept_only(valid_inputs, input);
  }
  return input;
}

double calc_time(double distance, double speed) {
  return distance / speed;
}

/** Interface Functions **/

/** Retrieve user input and validate the inputs **/
auto get_user_input() {
  std::string units =      prompt("Select your units. M: Miles, K: Kilometers: [M/K]: ");
  double distance   = atof(prompt("Enter your trip distance: ").c_str());
  while (distance < 0) {
  }
  double speed      = atof(prompt("Enter your vehicle's speed in kilometers per minute (km/m): ").c_str());
  return std::make_tuple(units, distance, speed);
}

/** Get oil level of user's vehicle **/
int get_oil_level() {
  std::string oil_level_prompt = "What is the oil level indicated by your vehicle's dipstick?\n";
  oil_level_prompt += "\t0: Below minimum\n";
  oil_level_prompt += "\t1: Between minimum and maximum\n";
  oil_level_prompt += "\t2: Above maximum\n";
  oil_level_prompt += "[0, 1, 2]: ";

  // Prompt for valid oil levels, and discard any other value
  ValidInput valid_oil_levels { "0", "1", "2" };
  std::string oil_level_str = accept_only_valid_inputs(
      oil_level_prompt.c_str(),
      ERROR_INVALID_INPUT,
      valid_oil_levels
      );

  // Convert the oil level to an integer value
  int oil_level = atoi(oil_level_str.c_str());

  return oil_level;
}

/** Get valid information about user's vehicle **/
auto get_vehicle_condition() {
  printf("Allow us to check the safety of your vehicle. Please answer the following questions.\n");

  auto oil_level = get_oil_level();

  // Prompt for valid yes or no inputs and discard any other value
  ValidInput valid_yes_or_no_inputs { "Yes", "yes", "No", "no" };

  // Reduce code duplication with closure
  // Note we don't have to pass in ERROR_INVALID_INPUT explicitly as it's captured by the lambda
  auto accept_only_yes_or_no = [&] (const char* prompt) -> std::string {
      return accept_only_valid_inputs(
        prompt,
        ERROR_INVALID_INPUT,
        valid_yes_or_no_inputs
      );
  };

  // Continually prompt for user input, and accept only the specified yes or no validated inputs
  std::string tire_pressure = accept_only_yes_or_no("Are your front and rear tire pressures between 30 and 35 psi? Answer [Yes/No]: ");
  std::string engine_temp_light = accept_only_yes_or_no("Is your engine temperature warning light on? Answer [Yes/No]: ");
  std::string battery_alert_light = accept_only_yes_or_no("Is the battery alert light on? Answer [Yes/No]:");
  
  return std::make_tuple(oil_level, tire_pressure, engine_temp_light, battery_alert_light);
}

int main () {
  // First we prompt the user for the trip and transportation information
  auto [units, distance, speed] = get_user_input();

  switch (toupper(units[0])) {
    case 'M': break;
    case 'K': break;
  }
  
  // Then we calculate the estimated time of arrival for the trip
  double eta = calc_time()
  
  get_vehicle_condition();
  return 0;
}
