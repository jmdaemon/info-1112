#include <iomanip>
#include <iostream>

double sq(double x) {
  return (x * x);
}

/** Calculates the height of the ball at some time
  * NOTE: 
  * - time is in seconds
  * - height is in metres */
double height(double time) {
  return (128 * time) - (16 * sq(time));
}

/** Calculates the velocity of the ball at some time
  * NOTE: 
  * - time is in seconds
  * - velocity is in metres per second */
double velocity(double time) {
  return 128 - (32 * time);
}

void show(double time) {
  // Show the inital problem
  auto print_indent = [](const char* s) { std::cout << std::setw(8) << s << std::endl; };
  std::cout << "A ball is thrown upwards in the air. The following functions describe the motion of the ball.\n";
  print_indent("h(t) = 128t - 16t^2");
  print_indent("v(t) = 128 - 32t");

  // Complete the problem
  double displacement = height(time);
  double velocity_final = velocity(time);
  std::cout << "The height and velocity of a ball at " << time << " seconds is: \n";

  auto print_indent_units = [](const char* msg, auto var, const char* units) {
    std::cout << std::setw(8) << std::left << msg << var << units << std::endl;
  };
  print_indent_units("Displacement: ", displacement, "m");
  print_indent_units("Velocity: " , velocity_final, "m^2");
}

int main() {
  double time = -48.0;
  show(time);
  return 0;
}
