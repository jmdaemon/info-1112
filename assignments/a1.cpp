#include <iostream>
#include <string>
#include <tuple>

#include <cstdio>

/** Library Functions **/

/** Prompts a user for input from the command line */
std::string prompt(const char* msg) {
  std::string input;
  printf("%s", msg);
  std::cin >> input;
  return input;
}

/** Returns true if the input was valid, and false otherwise **/
bool accept_only(std::string valid_inputs[], std::string input) {
  for (auto valid_input = valid_inputs->begin(); valid_input != valid_inputs->end(); ++valid_input) {
    if (input == valid_input.base())
      return true;
  }
  return false;
}

/** Continually prompts for an input until a valid input is given **/
std::string accept_only_valid_inputs(const char* msg, const char* error_prompt, std::string valid_inputs[]) {
  // Get user input
  std::string input = prompt(msg);

  // If input is invalid
  bool input_is_valid = accept_only(valid_inputs, input);
  while (!input_is_valid) {
    // Display the error message
    printf("%s", error_prompt);

    // Force user to give valid input
    input = prompt(msg);

    // Check if the new input is valid
    input_is_valid = accept_only(valid_inputs, input);
  }
  return input;
}

/** Interface Functions **/
auto get_user_input() {
  std::string units =      prompt("Select your units. M: Miles, K: Kilometers: [M/K]: ");
  double distance   = atof(prompt("Enter your trip distance: ").c_str());
  double speed      = atof(prompt("Enter your vehicle's speed in kilometers per minute (km/m): ").c_str());
  return std::make_tuple(units, distance, speed);
}

auto get_vehicle_condition() {
  printf("Allow us to check the safety of your vehicle. Please answer the following questions.\n");

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

  std::string oil_levels[] = { "0", "1", "2" };

  // Get the oil level as an integer, and validate the input
  const char* oil_level_str = accept_only_valid_inputs(
        oil_level_prompt.c_str(),
        invalid_input,
        oil_levels
        //{ "0", "1", "2" }
      ).c_str();
  int oil_level = atof(oil_level_str);

  // Accepts only "Yes", "yes", "No", "no" inputs
  // Only these answers may be given, any other answers are silently ignored
  auto accept_only_yes_or_no = [&] (const char* prompt) -> std::string {
    std::string accepted_inputs[] = { "Yes", "yes", "No", "no" };
      return accept_only_valid_inputs(
        prompt,
        invalid_input,
        accepted_inputs
      );
  };

  //std::string tire_pressure;
  //printf("Are your front and rear tire pressures between 30 and 35 psi? Answer [Yes/No]: ");
  //std::cin >> tire_pressure;
  std::string tire_pressure = accept_only_yes_or_no("Are your front and rear tire pressures between 30 and 35 psi? Answer [Yes/No]: ");
  std::string engine_temp_light = accept_only_yes_or_no("Is your engine temperature warning light on? Answer [Yes/No]: ");
  std::string battery_alert_light = accept_only_yes_or_no("Is the battery alert light on? Answer [Yes/No]:");
  //std::string engine_temp_light;
  //printf("Is your engine temperature warning light on? Answer [Yes/No]: ");
  //std::cin >> engine_temp_light;

  //std::string battery_alert_light;
  //printf("Is the battery alert light on? Answer [Yes/No]:");
  
  return std::make_tuple(oil_level, tire_pressure, engine_temp_light, battery_alert_light);
}

int main () {
  get_user_input();
  //get_vehicle_condition();
  return 0;
}
