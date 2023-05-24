#include <iomanip>
#include <iostream>
#include <tuple>

#include <cstdio>

// Obtain user's height and weight
auto get_user_data() {
  double weight, height;

  std::cout << "Please enter your weight (lbs): ";
  std::cin >> weight;

  std::cout << "Please enter your height (inches): ";
  std::cin >> height;

  return std::make_tuple(weight, height);
}

double calc_hat_size (double weight, double height) {
  return 2.9 * (weight / height);
}

double calc_jacket_size (double weight, double height) {
  return (height * weight) / 288.0;
}

double calc_waist_size (double weight) {
  return (weight / 4.9);
}

void show(double weight, double height) {
  // Round decimal numbers to whole numbers
  std::cout << std::fixed << std::noshowpoint << std::setprecision(0);

  auto print_aligned = [](const char* msg, auto var) {
    std::cout << std::setw(24) << std::left << msg << std::right << var << std::endl;
  };

  auto print_size = [&](const char* size_variant, double size) {
    std::string s = "Your ";
                s += std::string(size_variant);
                s += " size is: ";
    print_aligned(s.c_str(), size);
  };

  print_size("hat", calc_hat_size(weight, height));
  print_size("jacket", calc_jacket_size(weight, height));
  print_size("waist", calc_waist_size(weight));
}

int main(int argc, char** argv) {
  auto [weight, height] = get_user_data();
  show(weight, height);
  return 0;
}
