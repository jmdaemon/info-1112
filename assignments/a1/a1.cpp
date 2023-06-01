/*
   INFO 1112 S10
   Joseph Diza
   100427500
   2023-06-01
*/

#include <iostream>
#include <string>

#include <cstdio>
#include <tuple>

auto get_user_input() {
  std::string fname, lname, address;

  //std::cout << "Please enter your first and last name: ";
  printf("Please enter your first and last name: ");
  std::cin >> fname >> lname;
  
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
  return 0;
}
