#include <cstdio>
#include <cstdlib>

#include <iomanip>
#include <iostream>

double calc_material_resistance(double length, double cross_sect_area, double resitivity) {

  return ((resitivity * length) / cross_sect_area);
}

void show(const char* arg1, const char* arg2, const char* arg3) {
  // Convert strings arguments to doubles
  double length           = atof(arg1);
  double cross_sect_area  = atof(arg2);
  double resitivity       = atof(arg3);

  //const char* summary_format = "The material resistance for a material of \n\tlength %s of %s and %s is %.2f\n";
  
  auto print_aligned = [](const char* msg, const char* var) -> void {
    std::cout << std::setw(24) << std::left << msg << std::right << var << std::endl;
  };
  std::cout << "For a material with the following requirements\n";
  //std::cout << std::setw(16) << std::left << "Length" << std::right << arg1;
  print_aligned("Length", arg1);
  print_aligned("Cross Sectional Area", arg2);
  print_aligned("Resitivity", arg3);

  double resistance = calc_material_resistance(length, cross_sect_area, resitivity);
  std::cout << "The material resistance is " << resistance << "Ω\n";
}


int main(int argc, char** argv) {
  // Process command line arguments
  if ((argc < 4) || (argc > 4)) {
    puts("Error. Invalid number of arguments.");
    printf("Usage: %s [length (m)] [cross sectional area (m^2)] [resitivity (Ohm-Meters)]\n", argv[0]);
    return -1;
  }

  show(argv[1], argv[2], argv[3]);
}
