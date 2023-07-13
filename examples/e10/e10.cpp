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
  return distribution * (max - min) + min;
}

// 2: Comparing float values
double dsum(double array[], size_t size) {
  double sum = 0;
  for (size_t i = 0; i < size; i++) {
    sum += array[i];
  }
  return sum;
}

double davg(double array[], size_t size) {
  double sum = dsum(array, size);
  return sum / (double) size;
}

// Find the position of the minimum value in an array
// If the array is empty, the value returned will be -1
double d_min_index(double array[], size_t size) {
  size_t min = -1;
  for (size_t i = 0; i < size; i++)
    if (array[min] > array[i])
      min = i;
  return min;
}

// Find the position maximum value in an array
// If the array is empty, the value returned will be -1
double d_max_index(double array[], size_t size) {
  size_t max = -1;
  for (size_t i = 0; i < size; i++)
    if (array[max] < array[i])
      max = i;
  return max;
}

int main() {
  const size_t MAX = 100;
  const size_t MIN = 2;

  set_random_seed();
  const size_t n = 20;
  for (size_t i = 0; i < n; i++)
    printf("%f\n", gen_random_double(MIN, MAX));
}
