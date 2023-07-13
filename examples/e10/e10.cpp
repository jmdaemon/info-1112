#include <algorithm>
#include <array>
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

// 2: Comparing float values
template <size_t T>
//double dsum(std::array<double, T> array) {
double dsum(double (&array)[T]) {
  return std::accumulate(std::begin(array), std::end(array), 0.0, [] (double x, double y) { return x + y; });

//double dsum(std::array<double, 10> array, size_t size) {
  //return std::accumulate(std::begin(array), std::end(array), 0.0, [] (double x, double y) { return x + y; });

//double dsum(double array[], size_t size) {
  //int sum = 0;
  //std::for_each(std::begin(array), std::end(array), [&sum](int v) { sum += v; });
  //return sum;

  //double sum = 0;
  //for (size_t i = 0; i < size; i++) {
    //sum += array[i];
  //}
  //return sum;
}

//double davg(double array[], size_t size) {
template <size_t size>
double davg(double (&array)[size]) {
  double sum = dsum(array);
  return sum / (double) size;
}

// Find the position of the minimum value in an array
// If the array is empty, the value returned will be -1
int d_min_index(double array[], size_t size) {
  size_t min = -1;
  for (size_t i = 0; i < size; i++)
    if (array[min] > array[i])
      min = i;
  return min;
}

// Find the position maximum value in an array
// If the array is empty, the value returned will be -1
int d_max_index(double array[], size_t size) {
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
