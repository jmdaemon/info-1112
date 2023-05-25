#include <iostream>
#include <cstdio>

auto get_user_input() {
  int minutes;
  std::cout << "Please enter the current PDT time in minutes: ";
  std::cin >> minutes;
  return minutes;
}

int mm_get_hh(int minutes) {
  return minutes / 60;
}

int mm_get_hh_remainder(int minutes) {
  int hh = mm_get_hh(minutes);
  return (minutes - hh * 60);
}

int pdt_to_edt(int hours) {
  return hours + 3;
}
int pdt_to_adt(int hours) {
  return hours + 4;
}

void show(int minutes) {
  // Convert the time to hours
  int hours_pdt = mm_get_hh(minutes);

  // Convert the pdt time to the different time zones
  int hours_edt = pdt_to_edt(hours_pdt);
  int hours_adt = pdt_to_adt(hours_pdt);

  // Show the current time
  const char* display_format = "%d:%d\n";
  
  auto show_time = [&](int hh, int minutes) {
    int mm = mm_get_hh_remainder(minutes);
    printf(display_format, hh, mm);
  };

  show_time(hours_pdt, minutes);
  show_time(hours_adt, minutes);
  show_time(hours_edt, minutes);
  
}

int main() {
  show(get_user_input());
  return 0;
}
