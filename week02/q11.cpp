#include <iostream>
#include <iomanip>

using namespace std;

// Q: What is the output of the following program? Assume the input given is: 10 100 1.5 +
//  int num1, num2;
//  float num3;   char C;
//  cin >> num1 >> num2 >> num3 >> C;
//  cout << setfill('#');
//  cout << fixed << showpoint;
//  cout << "num1 = " << setw(10) << num1 << endl;
//  cout << "num2 = " << setw(10) << num2 << endl;
//  cout << "num3 = " << setw(10) << setprecision(2)<<num3 << endl;
//  cout << setw(4) << C <<" = " << setw(10)<< num1 + num2 + num3<< endl;
int main() {
  // Attempt #1
  //int num1, num2;                                                       // Declaration of two integer numbers
  //float num3;   char C;                                                 // Declaration of a float number and a character
  //cin >> num1 >> num2 >> num3 >> C;                                     // num1 = 10, num2 = 100, num3 = 1.5, C = +
  //cout << setfill('#');                                                 // Sets the fill character to '#'
  //cout << fixed << showpoint;                                           // Shows the full floating point value without truncation
  //cout << "num1 = " << setw(10) << num1 << endl;                        // Outputs: "num1 = #10"
  //cout << "num2 = " << setw(10) << num2 << endl;                        // Outputs: "num2 = 100"
  //cout << "num3 = " << setw(10) << setprecision(2)<<num3 << endl;       // Outputs: "num3 = #1.5"
  //cout << setw(4) << C <<" = " << setw(10)<< num1 + num2 + num3<< endl; // Outputs: "+ = #######110"

  // Attempt #2
  int num1, num2;                                                       // Declaration of two integer numbers
  float num3;   char C;                                                 // Declaration of a float number and a character
  cin >> num1 >> num2 >> num3 >> C;                                     // num1 = 10, num2 = 100, num3 = 1.5, C = +
  cout << setfill('#');                                                 // Sets the fill character to '#'
  cout << fixed << showpoint;                                           // Shows the full floating point value without truncation
  cout << "num1 = " << setw(10) << num1 << endl;                        // (1) Outputs: "num1 = ########10"
  cout << "num2 = " << setw(10) << num2 << endl;                        // (2) Outputs: "num2 = #######100"
  cout << "num3 = " << setw(10) << setprecision(2)<<num3 << endl;       // (3) Outputs: "num3 = ######1.50"
  cout << setw(4) << C <<" = " << setw(10)<< num1 + num2 + num3<< endl; // (4) Outputs: "###+ = ####111.50"
  // (1) Remember that setw(n) reserves a block of whitespace of n characters
  // setfill(c) affects the block of characters used to pad the setw(n) block
}
