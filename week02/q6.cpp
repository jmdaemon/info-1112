#include <iostream>
#include <cstdio>

#include <tuple>

double calc_area_rect(double length, double width) {
  return length * width;
}

double calc_perimeter_rect(double length, double width) {
  return (2 * length) + (2 * width);
}

auto get_user_input() {
  double length, width;
  
  std::cout << "Rectangle Calculator\n";
  std::cout << "Please enter the length of the rectangle: ";
  std::cin >> length;

  std::cout << "Please enter the width of the rectangle: ";
  std::cin >> width;

  return std::make_tuple(length, width);
}

void show(double length, double width) {
  const char* display_format = "The rectangle has an %s of %.2f\n";
  printf(display_format, "area", calc_area_rect(length, width));
  printf(display_format, "perimeter", calc_perimeter_rect(length, width));
}

int main() {
  auto [length, width] = get_user_input();
  show(length, width);
  return 0;
}
