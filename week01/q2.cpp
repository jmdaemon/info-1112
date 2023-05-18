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
  return (sum(x, y) / 2.0);
}

void summarize(char* arg1, char* arg2) {
  // Convert strings arguments to doubles
  // NOTE: The conversion from string to double is done directly since
  // we still require the input strings in the summarize format to display the values
  double x = atof(arg1);
  double y = atof(arg2);

  const char* summary_format = "The %s of %s and %s is %.2f\n";

  printf(summary_format, "sum", arg1, arg2, sum(x,y));
  printf(summary_format, "product", arg1, arg2, multiply(x,y));
  printf(summary_format, "average", arg1, arg2, average(x,y));
}

int main(int argc, char** argv) {
  // Process command line arguments
  if ((argc < 3) || (argc > 3)) {
    puts("Error. Invalid number of arguments.");
    printf("Usage: %s [x] [y]\n", argv[0]);
    return -1;
  }

  summarize(argv[1], argv[2]);
  return 0;
}
