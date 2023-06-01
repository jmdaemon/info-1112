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
  // Prompt user for first and last names
  std::string fname, lname, address;
  printf("Please enter your first and last name: ");
  std::cin >> fname >> lname;
  
  // Prompt for address
  std::cin.ignore(); // Clear the buffer
  printf("Please enter your full address: ");
  getline(std::cin, address);

  // Prompt for institution
  std::string student_choice;
  printf("Are you a KPU student, %s? [Yes/No] or [yes/no]: ", fname.c_str());
  std::cin >> student_choice;

  return std::make_tuple(fname, lname, address, student_choice);
}

// Direct KPU students to appropriate student advisor
void show_student_advisor(std::string student_choice) {
  if (student_choice == "Yes" || student_choice == "yes") {
    char student_type;
    printf("Are you an International or Domestic KPU student? [I/D]: ");
    std::cin >> student_type;

    if (student_type =='I' || student_type == 'i')
      puts("Please see an international advisor");
    else if (student_type =='D' || student_type == 'd')
      puts("Please see a domestic advisor");
    else {
      puts("Error: Your choice is invalid. Please input either I or D");
      puts("Exiting program.");
      exit(-1);
    }
  } else if (student_choice == "No" || student_choice == "no") {
    puts("Thank you for completing our short survey");
    // Do nothing
  }
}

void show() {
  auto [fname, lname, address, student_choice] = get_user_input();
  printf("Your full name is %s %s\n", fname.c_str(), lname.c_str());
  printf("You live at %s\n", address.c_str());
  show_student_advisor(student_choice);
}

int main() {
  show();
  // Pause the executable for some time until the user decides to quit.
  #ifdef __linux__
    puts("Hit CTRL^C to exit...");
    pause(); // To quit, user must CTRL^C
  #elif _WIN32
    system("pause");
  #endif
  return 0;
}
