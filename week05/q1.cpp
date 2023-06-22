#include <iostream>
#include <iomanip>
#include <cstdio>

void populate_employee_ages(int employee_ages[4]) {
  int age = 0;
  while (age >= 0) {
    printf("Enter an employee age. (Note: To stop reading data, enter a negative integer): ");
    std::cin >> age;

    switch(age / 10) {
      case(1): case(2): employee_ages[0]++; break;
      case(3): employee_ages[1]++; break;
      case(4): employee_ages[2]++; break;
      case(5): employee_ages[3]++; break;
    }
  }
}

void show_employee_ages(int employee_ages[4]) {
  // Functions for printing with output
  auto print_col = [](int spaces, auto text) {
    std::cout << std::left << std::setw(spaces) << text;
  };
  auto print_gapsize_10 = [&](auto text) { print_col(10, text); };
  auto print_gapsize_4 = [&](auto text) { print_col(4, text); };
  auto print_row = [&](auto col1, auto col2) {
    print_gapsize_10(col1); print_gapsize_4(col2); puts("");
  };
  
  std::cout << "Number of Employees in each Age Group" << std::endl;
  print_row("Under 30", employee_ages[0]);
  print_row("30-40", employee_ages[1]);
  print_row("41-50", employee_ages[2]);
  print_row("Above 50", employee_ages[3]);
}

int main() {
  int employee_ages[4] = {0,0,0,0};
  populate_employee_ages(employee_ages);
  show_employee_ages(employee_ages);
  return 0;
}
