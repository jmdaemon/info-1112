#include <iostream>
#include <cstdio>

void set_random_seed() {
  srand(time(0));
}

// Generate a random double between 0.0 and 1.0
double gen_random_distribution() {
  return ((double) rand() / (double) RAND_MAX);
}

// Generate a random double between min and max
double gen_random_double(double min, double max) {
  double distribution = gen_random_distribution();
  return distribution * max + min;
}

int main() {
  const int MAX = 100;
  const int MIN = 2;

  set_random_seed();
  const int n = 20;
  for (int i = 0; i < n; i++)
    printf("%f\n", gen_random_double(MIN, MAX));
}
