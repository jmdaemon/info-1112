#include <iostream>

#include <cstdio>
#include <cstdlib>

double calc_standard_pay(int wage, int hours) {
  return (wage * hours);
}

// Assume you get paid 1 and a half times more for overtime
double calc_overtime_pay(int wage, int hours) {
  return (1.5 * wage * hours);
}

double calc_weekly_pay(int wage, int hours) {
  double salary = 0.0;
  if (hours > 40) {
    // Calculate overtime pay
    int standard_hours = hours - 40;
    int overtime_hours = hours - standard_hours;

    salary = calc_standard_pay(wage, standard_hours);
    salary += calc_overtime_pay(wage, overtime_hours);
  } else {
    salary = calc_standard_pay(wage, hours);
  }
  return salary;
}

void show_weekly_salary(double wage, int hours) {
  const char* display_format = "Your pay for this week is: $%.2f\n";
  printf(display_format, calc_weekly_pay(wage, hours));
}

int main(int argc, char** argv) {
  double wage;
  int hours;

  // Process command line arguments
  if ((argc < 3) || (argc > 3)) {
    // If no valid commmand line arguments are given
    std::cout << "Weekly Wage Calculator\n";
    std::cout << "Please enter your wage rate ($/hr): ";
    std::cin >> wage;
    std::cout << "Please enter your hours worked this week: ";
    std::cin >> hours;
  } else {
    wage = atof(argv[1]);
    hours = atof(argv[2]);
  }

  show_weekly_salary(wage, hours);

  return 0;
}
