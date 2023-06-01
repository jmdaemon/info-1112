/*
   INFO 1112 S10
   Joseph Diza
   100427500
   2023-06-01
*/

#include <iostream>
#include <string>
#include <tuple>

#include <cstdio>

// Includes `pause()` on Linux
#ifdef __linux__
     #include <unistd.h>
#endif

auto get_user_input() {
  std::string fname, lname, address;

  printf("Please enter your first and last name: ");
  std::cin >> fname >> lname;
  
  std::cin.ignore(); // Clear the buffer
  printf("Please enter your full address: ");
  getline(std::cin, address);

  return std::make_tuple(fname, lname, address);
}

void show() {
  auto [fname, lname, address] = get_user_input();
  printf("Your full name is %s %s\n", fname.c_str(), lname.c_str());
  printf("You live at %s\n", address.c_str());
}

int main() {
  show();
  // Pause the executable for some time until the user decides to quit.
  #ifdef __linux__
    pause(); // To quit, user must CTRL^C
  #elif _WIN32
    system("pause");
  #endif
  return 0;
}
