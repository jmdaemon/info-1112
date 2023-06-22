#include <iostream>
#include <vector>

typedef std::vector<int> Integers;

Integers get_integers_input() {
  std::vector<int> integers;
  int integer;
  while(integer > 0) {
    printf("Enter positive integers only. Integers less than or equal to zero will exit the prompt: ");
    std::cin >> integer;
    if (integer > 0)
      integers.push_back(integer);
  }
  return integers;
}

bool is_odd(int integer) {
  return (integer % 2) != 0;
}

int find_largest_odd_number(Integers integers) {
  int max = 0;
  for (auto integer: integers) {
    if (is_odd(integer) && integer > max)
      max = integer;
  }
  return max;
}

int find_number_of_odd_numbers(Integers integers) {
  int count = 0;
  for (auto integer: integers) {
    if (is_odd(integer))
      count++;
  }
  return count;
}

void show(Integers integers) {
  int count = find_number_of_odd_numbers(integers);
  int max = find_largest_odd_number(integers);

  printf("There are %d odd numbers\n", count);
  printf("The maximum odd number is %d\n", max);
}

int main() {
  Integers integers = get_integers_input();
  show(integers);
  return 0;
}
