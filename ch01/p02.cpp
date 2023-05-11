#include <cstdio>
#include <cstdlib>

#include <string>

double sum(double x, double y) {
  return x + y;
}

double multiply(double x, double y) {
  return x * y;
}

double average(double x, double y) {
  return sum(x, y) / 2.0;
}

void summarize(double x, double y) {
  const char* summary_format = "The %s of %.2f and %.2f is %.2f\n";

  printf(summary_format, "sum", x, y, sum(x,y));
  printf(summary_format, "product", x, y, multiply(x,y));
  printf(summary_format, "average", x, y, average(x,y));
}

int main(int argc, char** argv) {
  // Process command line arguments
  if ((argc < 3) || (argc > 3)) {
    puts("Error. Invalid number of arguments.");
    printf("Usage: %s [x] [y]\n", argv[0]);
    return -1;
  }
  
  // Convert strings arguments to doubles
  char* arg1 = argv[1];
  char* arg2 = argv[2];
  
  double x = atof(arg1);
  double y = atof(arg2);

  summarize(x, y);
  return 0;
}
