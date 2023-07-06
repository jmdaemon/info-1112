#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

// Types
typedef unsigned int NatNumber ;
typedef std::vector<NatNumber> RandomNumbers;

// Functions
void set_random_seed() {
  srand(time(0));
}

int gen_random_number(const NatNumber min, const NatNumber max) {
  return rand() % (max - min + 1) + min;
}

RandomNumbers gen_random_numbers(const NatNumber min, const NatNumber max, const NatNumber n) {
  RandomNumbers random_numbers;
  for (auto i = 0; i < 25; i++) {
    random_numbers.push_back(gen_random_number(min, max));
  }
  return random_numbers;
}

// Main
int main() {
  const NatNumber MIN = 1;
  const NatNumber MAX = 10;
  
  // Create file
  std::ofstream output_file("output.txt");
  if (!output_file) {
    puts("Error: File could not be created");
    exit(EXIT_FAILURE);
  }

  // Generate random numbers
  set_random_seed();
  RandomNumbers random_numbers = gen_random_numbers(MIN, MAX, 25);

  // Write to file
  for (auto number : random_numbers)
    output_file << number << std::endl;

  // Ensure the file is always closed
  output_file.close();
  return EXIT_SUCCESS;
}
