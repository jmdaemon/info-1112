#include <iostream>
#include <cstdio>

void set_random_seed() {
  srand(time(0));
}

//int gen_random_number(const NatNumber min, const NatNumber max) {
  //return rand() % (max - min + 1) + min;
//}

// Generate a random double between 0.0 and 1.0
double gen_random_distribution(double min, double max) {
  double distribution = ((double) rand() / (double) RAND_MAX);
  return distribution * max;
}

// Generate a random double between min and max
double gen_random_double(double min, double max) {
  //return (rand() / MAX) * MAX;
  //return rand() / (max - min) + min;
  //return ((double) rand() / (double) (max - min) + min);
  //return ((double) rand() / (double) max);
  
  double distribution = ((double) rand() / (double) RAND_MAX);
  //return (distribution / (max - min)) + min;
  //return distribution * max;
  //return (distribution * (max - min)) + min;
  return distribution * max + min;
}

int main() {
  const int MAX = 100;
  const int MIN = 2;

  set_random_seed();
  const int n = 20;
  for (int i = 0; i < n; i++)
    printf("%f\n", gen_random_double(MIN, MAX));
    //std::cout << gen_random_double(MAX, MIN) << std::endl;
}
