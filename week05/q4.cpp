#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

const int STUDENT_COUNT = 10;
typedef std::vector<double> Students;

bool double_is_equals(double val1, double val2) {
  return fabs(val2 - val1) == 0;
}

int count_matching_doubles(double match_with, std::vector<double> values) {
  int count = 0;
  for (auto val: values) {
    if (double_is_equals(val, match_with))
      count++;
  }
  return count;
}

int main() {
  Students students(10);
  for (int i = 1; i < STUDENT_COUNT; i++) {
    double gpa;
    printf("Enter student's GPA for %i students", (STUDENT_COUNT - i + 1));
    std::cin >> gpa;
    students.push_back(gpa);
  }

  int n = count_matching_doubles(4.0, students);
  int percent_students = (n / 10.0) * 100;
  printf("There are %d students with a 4.0 GPA.\n", n);
  printf("They represent %d\%% of the students.\n", percent_students);
  return 0;
}
