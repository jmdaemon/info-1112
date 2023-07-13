#include <iostream>
#include <cstdio>

// 1:
// Set the seed for random number generation
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

// 2: Comparing float values
double dsum(double array[], int size) {
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += array[i];
  }
  return sum;
}

double davg(double array[], int size) {
  double sum = dsum(array, size);
  return sum / (double) size;
}

// Find the minimum value in an array
// If the array is empty, the minimum returned will be -1
double d_min(double array[], int size) {
  int min = -1;
  for (int i = 0; i < size; i++)
    if (min < array[i])
      min = array[i];
  return min;
}

int main() {
  const int MAX = 100;
  const int MIN = 2;

  set_random_seed();
  const int n = 20;
  for (int i = 0; i < n; i++)
    printf("%f\n", gen_random_double(MIN, MAX));
}
