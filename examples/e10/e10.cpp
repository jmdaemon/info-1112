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
template <size_t SIZE>
double dsum(double (&array)[SIZE]) {
  return std::accumulate(std::begin(array), std::end(array), 0.0, [] (double x, double y) { return x + y; });
}

template <size_t SIZE>
double davg(double (&array)[SIZE]) {
  double sum = dsum(array);
  return sum / (double) SIZE;
}

// Search for a specific value based on a target
template <typename T>
int bsearch (T array[], T left, T, T right, T target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
 
        // Check if x is present at mid
        if (array[mid] == target)
            return mid;
 
        // If x greater, ignore left half
        if (array[mid] < target)
            left = mid + 1;
 
        // If x is smaller, ignore right half
        else
            right = mid - 1;
    }
 
    // If we reach here, then element was not present
    return -1;
}

// Find the position of the minimum value in an array
// If the array is empty, the value returned will be -1
int bsearch_double_min(double array[], size_t size) {
  if (size <= 0) return -1;

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

template <size_t SIZE>
void populate_random_numbers(double (&array)[SIZE], double min, double max) {
  for (int i = 0; i < SIZE; i++)
    array[i] = gen_random_double(min, max);
}

int main() {
  const size_t MAX = 100;
  const size_t MIN = 2;

  const size_t n = 20;
  double array[n] {};
  //for (size_t i = 0; i < n; i++)
    //printf("%f\n", gen_random_double(MIN, MAX));

  set_random_seed();
  populate_random_numbers(array, MIN, MAX);
}
