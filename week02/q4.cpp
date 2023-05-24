#include <cstdio>
#include <cstdlib>
#include <cmath>

double y(double x) {
  auto rat_exp = [](double x) -> double {
    return (x - 3) / (2 * x + 1);
  };

  return (rat_exp(x) - (pow(3, x)) + 4);
}

void display(double x) {
  double output = y(x);
  printf("y(%.2f) = %.2f\n", x, output);
}

int main(int argc, char** argv) {
  // Process command line arguments
  if ((argc < 2) || (argc > 2)) {
    puts("Error. Invalid number of arguments.");
    printf("Usage: %s [number]\n", argv[0]);
    return -1;
  }

  double x = atof(argv[1]);

  display(x);
}

