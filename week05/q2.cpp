#include <iostream>
#include <iomanip>
#include <cstdio>

// Determine if a value is in a specified range (inclusive)
bool in_range_i(int min, int max, int val) {
  return (val >= min && val <= max);
}

void populate_patient_counts(int patient_counts[3]) {
  int blood_sugar_level = 0;
  while (blood_sugar_level >= 0) {
    printf("Enter an patient blood_sugar_level. (Note: To stop reading data, enter a negative integer): ");
    std::cin >> blood_sugar_level;

    if (in_range_i(0, 70, blood_sugar_level)) {
      patient_counts[0]++;
    } else if (in_range_i(70, 140, blood_sugar_level)) {
      patient_counts[1]++;
    } else if (blood_sugar_level > 140) {
      patient_counts[2]++;
    }
  }
}

void show(int patient_counts[3]) {
  // Functions for printing with output
  auto print_col = [](int spaces, auto text) {
    std::cout << std::left << std::setw(spaces) << text;
  };
  auto print_gapsize_24 = [&](auto text) { print_col(24, text); };
  auto print_gapsize_4 = [&](auto text) { print_col(4, text); };
  auto print_row = [&](auto col1, auto col2) {
    print_gapsize_24(col1); print_gapsize_4(col2); puts("");
  };
  
  std::cout << "Number of Patients in each Blood Group Level" << std::endl;
  print_row("Below 70 mg/dL", patient_counts[0]);
  print_row("Between 70-140 mg/dL", patient_counts[1]);
  print_row("Above 140 mg/dL", patient_counts[2]);
}

int main() {
  int patient_counts[3] = {0,0,0};
  populate_patient_counts(patient_counts);
  show(patient_counts);
  return 0;
}
