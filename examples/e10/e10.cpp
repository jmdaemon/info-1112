#include <algorithm>
#include <numeric>
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

// 2. Populate Data
template <size_t SIZE>
void populate_random_numbers(double (&array)[SIZE], double min, double max) {
  for (int i = 0; i < SIZE; i++)
    array[i] = gen_random_double(min, max);
}

// 3: Comparing float values
template <size_t SIZE>
double dsum(double (&array)[SIZE]) {
  return std::accumulate(std::begin(array), std::end(array), 0.0, [] (double x, double y) { return x + y; });
}

template <size_t SIZE>
double davg(double (&array)[SIZE]) {
  return dsum(array) / (double) SIZE;
}

// Find the position of the minimum value in an array
// If the array is empty, the value returned will be -1
template <size_t SIZE>
size_t dmin_index(double (&array)[SIZE]) {
  size_t min = -1;
  std::for_each(std::begin(array), std::end(array), [&min](double x) { if (x < min) min = x; });
  return min;
}

// Find the position maximum value in an array
// If the array is empty, the value returned will be -1
template <size_t SIZE>
size_t dmax_index(double (&array)[SIZE]) {
  size_t max = -1;
  std::for_each(std::begin(array), std::end(array), [&max](double x) { if (x > max) max = x; });
  return max;
}

int main() {
  const size_t MAX = 100;
  const size_t MIN = 2;

  const size_t n = 20;
  double array[n] {};

  // Populate array
  set_random_seed();
  populate_random_numbers(array, MIN, MAX);
  
  int min_index = dmin_index(array);
  int max_index = dmax_index(array);
  int avg = davg(array);
}
