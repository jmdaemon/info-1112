#include <iostream>

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
  return minutes % 60;
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
  auto show_time = [&](int minutes, int hh, const char* timezone) {
    int mm = mm_get_hh_remainder(minutes);
    std::cout 
      << timezone << " minutes " << mm
      << " hours " << hh << std::endl;
  };

  show_time(minutes, hours_pdt, "PDT");
  show_time(minutes, hours_adt, "EDT");
  show_time(minutes, hours_edt, "ADT");
}

int main() {
  show(get_user_input());
  return 0;
}
