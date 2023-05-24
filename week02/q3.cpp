#include <iomanip>
#include <iostream>

double sq(double x) {
  return (x * x);
}

double height(double time) {
  return (128 * time) - (16 * sq(time));
}

double velocity(double time) {
  return 128 - (32 * time);
}

void show(double time) {
  auto print_indent = [](const char* s) { std::cout << std::setw(8) << s << std::endl; };
  std::cout << "A ball is thrown upwards in the air. The following functions describe the motion of the ball.\n";
  print_indent("h(t) = 128t - 16t^2");
  print_indent("v(t) = 128 - 32t");

  double displacement = height(time);
  double velocity_final = velocity(time);
  std::cout << "The height and velocity of a ball at " << time << " seconds is \n";

  auto print_indent_var = [](const char* s, auto var) { std::cout << std::setw(8) << s << var << std::endl; };

  print_indent_var("Displacement: ", displacement);
  print_indent_var("Velocity: " , velocity_final);
}

int main() {
  double time = -48.0;
  show(time);
  return 0;
}
