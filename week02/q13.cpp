#include <iostream>
#include <iomanip>

using namespace std;
// Q: What is the output of the following code?
//  char z='$';
//  double x=756.389;
//  int y=564;
//  cout<<fixed<<showpoint<<setprecision(5);
//  cout<<left;   cout<<setfill('*');
//  cout<<setw(10)<<y<<endl;
//  cout<<setw(10)<<x<<endl;
//  cout<<right;
//  cout<<setw(10)<<z<<endl; cout<<setw(10)<<2.56*1.5;

int main() {
  // Attempt 1
  //char z='$';                                       // Declare character z='$'
  //double x=756.389;                                 // Declare double x=756.389
  //int y=564;                                        // Declare y=564
  //cout<<fixed<<showpoint<<setprecision(5);          // Show decimal points, show 5 decimal places for floating point numbers
  //cout<<left;   cout<<setfill('*');                 // Left justify text for setw, set fill character to '*' for setw
  //cout<<setw(10)<<y<<endl;                          // Reserve block of 10 characters (of '*'), Outputs: "$*********"
  //cout<<setw(10)<<x<<endl;                          // Reserve block of 10 characters (of '*'), Outputs: "756.389***"
  //cout<<right;                                      // Right justify text for setw
  //cout<<setw(10)<<z<<endl; cout<<setw(10)<<2.56*1.5;// Reserve block of 10 characters (of '*'), Outputs: "*********$"
                                                    // Reserve block of 10 characters (of '*'), Outputs: "******3.84"
  // Attempt 2
  char z='$';                                       // Declare character z='$'
  double x=756.389;                                 // Declare double x=756.389
  int y=564;                                        // Declare y=564
  cout<<fixed<<showpoint<<setprecision(5);          // Show decimal points, show 5 decimal places for floating point numbers
  cout<<left;   cout<<setfill('*');                 // Left justify text for setw, set fill character to '*' for setw
  cout<<setw(10)<<y<<endl;                          // (1) Reserve block of 10 characters (of '*'), Outputs: "564*******"
  cout<<setw(10)<<x<<endl;                          // (2) Reserve block of 10 characters (of '*'), Outputs: "756.38900*"
  cout<<right;                                      // Right justify text for setw
  cout<<setw(10)<<z<<endl; cout<<setw(10)<<2.56*1.5;// Reserve block of 10 characters (of '*'), Outputs: "*********$"
                                                    // Reserve block of 10 characters (of '*'), Outputs: "****3.8400"
  // (1) Remember to not get confused with variables. You can declare them in any order and print them in any order.
  // Also remember to keep in mind the current fill character
  // (2) setprecision(n) reserves 'n' decimal digits of precision after the dot.
  // Anything that requries more precision is rounded, and anything with less is padded with zeroes to fill 'n' characters
}
