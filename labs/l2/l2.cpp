/**
  * Lab 2
  * Student Name  : Joseph Diza
  * Student Number: 100427500 
  * Course Name   : Info 1112 S10
  */

#include <iostream>
#include <cstdio>
#include <tuple>

// Employee Performance Level Functionality
enum PERFORMANCE_LEVEL {
  WEAK,
  ACCEPTED,
  GOOD,
  EXCELLENT,
};

const double PERFORMANCE_LEVEL_PAY_CHANGES[4] = {
  -10.0 / 100 , // WEAK
  5.0 / 100   , // ACCEPTED
  10.0 / 100  , // GOOD
  15.0 / 100  , // EXCELLENT
};

typedef unsigned short Performance;

bool in_range(int min, int max, int value) {
  return (value > min && value < max);
}

/** Get the performance level of an employee
  * Assume `performance` must a valid integer within the range 0-10 **/
PERFORMANCE_LEVEL get_perf_level(unsigned short performance) {
  PERFORMANCE_LEVEL perf_level
    = in_range(8, 10, performance) ? EXCELLENT
    : in_range(7, 8, performance) ? GOOD
    : in_range(5, 7, performance) ? ACCEPTED
    : WEAK;
  return perf_level;
}

const char* get_perf_desc(PERFORMANCE_LEVEL perf_level) {
  const char* perf_desc;
  switch(perf_level) {
    case EXCELLENT: perf_desc = "excellent"; break;
    case GOOD     : perf_desc = "good"; break;
    case ACCEPTED : perf_desc = "acceptable"; break;
    case WEAK     : perf_desc = "weak"; break;
  }
  return perf_desc;
}

double get_perf_scale(PERFORMANCE_LEVEL perf_level) {
  return PERFORMANCE_LEVEL_PAY_CHANGES[perf_level];
}

auto get_user_input() {
  double salary;
  printf("What is your salary in dollars?: $");
  std::cin >> salary;

  Performance performance;
  printf("What was the customer's feedback? [0-10]: ");
  std::cin >> performance;

  // If the performance is invalid, we will exit early, this will be when performance < 0 or performance > 10
  if (performance > 10) {
    puts("Invalid performance level. Performance level should be in the range 0-10.");
    exit(-1);
  }

  PERFORMANCE_LEVEL perf_level = get_perf_level(performance);
  return std::make_tuple(salary, perf_level);
}

// Employee Salary Functionality
double calc_change_in_pay(double salary, PERFORMANCE_LEVEL perf_level) {
  return salary * get_perf_scale(perf_level);
}

double calc_employee_salary(double salary, PERFORMANCE_LEVEL perf_level) {
  return salary + calc_change_in_pay(salary, perf_level);
}

void show_employee_salary(double salary, PERFORMANCE_LEVEL perf_level) {
  double new_salary = calc_employee_salary(salary, perf_level);
  const char* perf_desc = get_perf_desc(perf_level);

  printf("Your new salary is $%.2f, your performance was %s\n", new_salary, perf_desc);
}

int main() {
  // Get employee salary and performance level
  auto [salary, perf_level] = get_user_input();

  show_employee_salary(salary, perf_level);
  return 0;
}
