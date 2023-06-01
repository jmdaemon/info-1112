#include <iostream>

using namespace std;
int main() {
  int a = 10, y = 5, x;
  a *= 2;
  x = a + 7 / 3 * 6 % y;
  cout << a << " " << x;
  return 0;
}
