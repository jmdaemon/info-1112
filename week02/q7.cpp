#include <iostream>

#include <cmath>
#include <tuple>

auto get_user_input() {
  int time;
  std::cout << "Enter the elapsed time in whole seconds: ";
  std::cin >> time;
  return time;
}

auto seconds_to_24hr(int seconds) {
  double remainder = seconds / 3600.0;
  int hh = floor(remainder);

  remainder = ((remainder - hh) * 3600) / 60.0;
  int mm = floor(remainder);

  remainder = ((remainder - mm) * 3600) / 60.0;
  int ss = round(remainder);

  return std::make_tuple(hh, mm, ss);
}

void show_elapsed_time(int seconds) {
  auto [hh,mm,ss] = seconds_to_24hr(seconds);
  const char* display_format = "%d:%d:%d\n";
  printf(display_format, hh, mm, ss);
}

int main() {
  show_elapsed_time(get_user_input());
}
