#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

// Constants
const char* ERROR_FILE_CREATE = "Error: File could not be created";
const char* ERROR_FILE_OPEN   = "Error: File could not be found";

// Types
typedef unsigned int NatNumber;
typedef std::vector<NatNumber> RandomNumbers;
typedef std::map<NatNumber, NatNumber> NumberCounts;

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

// Ensure a file exists
template <typename T>
T ensure_file_exists(const char* filepath, const char* error_msg) {
  T file(filepath);
  if (!file) {
    puts(error_msg);
    exit(EXIT_FAILURE);
  }
  return file;
}

std::ofstream create_output_file(const char* filepath) {
  return ensure_file_exists<std::ofstream>(filepath, ERROR_FILE_CREATE);
}

std::fstream create_input_file(const char* filepath) {
  return ensure_file_exists<std::fstream>(filepath, ERROR_FILE_OPEN);
}

// Main
int main() {
  const NatNumber MIN = 1;
  const NatNumber MAX = 10;
  
  // Create file
  std::ofstream output_file = create_output_file("output.txt");

  // Generate random numbers
  set_random_seed();
  RandomNumbers random_numbers = gen_random_numbers(MIN, MAX, 25);

  // Write to file
  for (auto number : random_numbers)
    output_file << number << std::endl;

  // Ensure the file is always closed
  output_file.close();

  // Read from the input file
  std::fstream input_file = create_input_file("output.txt");

  // Count the input numbers
  int random_number;
  NumberCounts number_counts;
  while(!input_file.eof()) {
    input_file >> random_number;
    number_counts[random_number]++;
  }

  // Show the input numbers
  for (auto [number, count]: number_counts)
    printf("There are %d %d's\n", count, number);

  // Write to output file
  std::ofstream counts_file = create_output_file("counts.txt");
  const NatNumber WIDTH = 4;
  const std::string STAR = "*";
  for (auto [number, count]: number_counts) {
    //counts_file << std::left << std::setw(WIDTH) << number  << " = " << std::setw(WIDTH) << count << std::endl;
    counts_file << std::left << std::setw(WIDTH) << number  << " = ";
    //counts_file << std::setw(WIDTH);
    for (auto i = 0; i <= count; i++)
      counts_file << STAR;
    counts_file << std::endl;
  }

  return EXIT_SUCCESS;
}
