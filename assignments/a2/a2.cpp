/**
  * Student Name    : Joseph Diza
  * Student Number  : 100427500
  * Course Name     : INFO 1112 S10
  **/

#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

// Part I: Tom's Nursery Shop

// Constants
const unsigned int PRECISION = 3;

// Taxes
// Note: These are the tax amounts in B.C
const double PST = 0.07;
const double GST = 0.05;

// Types
typedef unsigned int Amount;
typedef double Price;

typedef struct Item {
  const char* name;
  Amount quantity;
  Price price;
} Item;

enum PLANT_TYPE {
  NONE,
  MONSTERA,
  PHILODENDRON,
  HOYA,
};

// Plants
Item Monstera      = {"Monstera"    , 20, 11.50};
Item Philodendron  = {"Philodendron", 20, 13.75};
Item Hoya          = {"Hoya"        , 20, 10.99};

std::map<PLANT_TYPE, Item*> Plants = {
  { MONSTERA, &Monstera },
  { PHILODENDRON, &Philodendron },
  { HOYA, &Hoya },
};

// Use a hashmap to bucket the items together
// We're going to batch the items together, and deal with any repeats by summing the quantities to each other
typedef std::map<PLANT_TYPE, Item> Cart;

// General Purpose Functions

// The standard library still doesn't have a map.contains() method???
template <typename K, typename V>
bool hashmap_contains(std::map<K, V> hashmap, K key) {
  return (hashmap.find(key) != hashmap.end());
}

bool strequals(const char* s1, const char* s2) {
  return (strcmp(s1, s2) == 0);
}

// Print newline
void ln() { puts(""); }

// Plant Functions
PLANT_TYPE get_plant_type(char c) {
  switch(c) {
    case('M'): return MONSTERA;
    case('P'): return PHILODENDRON;
    case('H'): return HOYA;
    default: return NONE;
  }
}

Item* get_plant_choice(PLANT_TYPE type) {
  return Plants[type];
}

Cart add_to_cart(Cart cart, Item* plant, PLANT_TYPE type, Amount amount) {
  // Queue the purchase
  Item purchase = { plant->name, amount, plant->price };

  // Deduct the stock
  plant->quantity -= amount;
  
  // If we already have one of that item type in our bucket
  if (hashmap_contains(cart, type)) {
    cart[type].quantity += amount; // Just add the amounts together
  } else {
    // Add to cart
    cart[type] = purchase;
  }
  return cart;
}

// User Input Functions
void display_option(char choice, const char* option) {
  char choice_alt = toupper(choice);
  printf("\t[%c|%c] for %s\n", choice_alt, choice, option);
};

// Get user's choice
char get_user_choice() {
  char choice;
  puts("Select from our plants below or checkout: ");
  display_option('m', "Monstera");
  display_option('p', "Philodendron");
  display_option('h', "Hoya");
  display_option('a', "Checkout");
  printf("Select: ");
  std::cin >> choice;

  return choice;
}

auto get_user_input() {
  char choice;
  Cart cart;

  puts("Welcome to Tom's Nursery Shop");
  while(choice != 'A') {
    choice = toupper(get_user_choice());
    PLANT_TYPE type = get_plant_type(choice);
    Item* plant = get_plant_choice(type);
    ln();
    if (plant == NULL) {
      // If the plant choice is invalid
      if (choice != 'A') {
        // TODO: Find way to clear input in case of null characters
        // Display an error 
        puts("Error: Invalid plant selected");
      }
      continue; // And prompt the user again
    }

    // Get valid amount to purchase
    Amount amount;
    printf("How many %s pots would you like to buy?: ", plant->name);
    std::cin >> amount;

    if (amount > plant->quantity) {
      ln();
      puts("Sorry. There are not enough of this plant available in stock.");
      printf("Amount Available: %d\n", plant->quantity);
      continue; // Return to prompt
    } 
    cart = add_to_cart(cart, plant, type, amount);
    ln();
  }
  return cart;
}

// Calculation Functions
double calc_cost(Item item) {
  return (item.price * item.quantity);
}

// Sum the cost of the goods
double calc_subtotal_cost(Cart cart) {
  double cost = 0;
  for (auto [_, item]: cart)
    cost += calc_cost(item);
  return cost;
}

// Apply PST and GST tax
double calc_total_cost(double cost) {
  return cost += (cost * (GST + PST));
}

void print_receipt(Cart cart) {
  auto print_plant_cost = [&](int amount, const char* name, double cost) {
    printf("%d %s plants cost $%.*f\n", amount, name, PRECISION, cost);
  };

  // Print receipt
  puts("Units/Description/Cost of Items");
  for (auto [_, item]: cart) {
    int amount = item.quantity;
    const char* name = item.name;
    double cost = calc_cost(item);
    print_plant_cost(amount, name, cost);
  }

  double subtotal = calc_subtotal_cost(cart);
  double total = calc_total_cost(subtotal);

  printf("Total amount before tax is $%.*f\n", PRECISION, subtotal);
  printf("Total amount after tax is $%.*f\n", PRECISION, total);
  
  ln();
  puts("Thank you! Please come again!");
}

// Part II: Loyalty Program Feature
#include <cmath>

typedef unsigned long Points;

std::string get_full_name() {
  std::string name;
  printf("Enter your full name: ");
  std::getline(std::cin, name, '\n');
  return name;
}

Points calc_loyalty_points(Cart cart) {
  Points points = 0;
  
  for (auto [_, item]: cart) {
    if (item.quantity > 1) {
      points += round(item.price / 0.75);
    }
  }
  return points;
}

void show_loyalty_points(const char* username, Cart cart) {
  Points points = calc_loyalty_points(cart);
  printf("You earned %ld points on this purchase, %s.\n", points, username);
}

// Part III: Print Table Receipt

// Constants
const unsigned int COL_WIDTH[4] = {
  16,
  10,
  10,
  10,
};
const unsigned int NAME_FIELD = COL_WIDTH[0] * 4;

// Prints a receipt in the following format:
// Customer       [name]
// Horizontal Line / Divider
// Plant          Amount      Cost ($)  Stock Left
// Monsterra      [amount]    [cost]    [plant.quantity]
// Philodendron   [amount]    [cost]    [plant.quantity]
// Hoya           [amount]    [cost]    [plant.quantity]
// Horizontal Line / Divider
// Cost           Amount ($)
// Subtotal       [subtotal]
// Total          [total]
// Loyalty Points [points]
//
// NOTE:
// Keep in mind that a receipt is not very wide horizontally
// So we need to print this table longer vertically instead
void print_receipt_table(const char* username, Cart cart) {
  // Helper functions for displaying the receipt in a table
  auto left_justify_output    = []() { std::cout << std::left; };
  auto show_n_decimal_places  = [](unsigned int n) { std::cout << std::fixed << std::setprecision(n); };
  auto set_fill_char          = [](char c) { std::cout << std::setfill(c); };
  
  // Print columns
  auto print_col = [](int width, auto text) { std::cout << std::left << std::setw(width) << text; };
  auto print_col1 = [&](auto text) { print_col(COL_WIDTH[0], text); };
  auto print_col2 = [&](auto text) { print_col(COL_WIDTH[1], text); };
  auto print_col3 = [&](auto text) { print_col(COL_WIDTH[2], text); };
  auto print_col4 = [&](auto text) { print_col(COL_WIDTH[3], text); };

  // Print rows
  auto print_2col_row = [&](auto col1, auto col2)
    { print_col1(col1); print_col2(col2); puts(""); };
  auto print_4col_row = [&](auto col1, auto col2, auto col3, auto col4)
    { print_col1(col1); print_col2(col2); print_col3(col3); print_col4(col4); puts(""); };

  // Print horizontal line
  auto print_hline = [&]()      { set_fill_char('='); print_4col_row("", "", "", ""); set_fill_char(' '); };
  auto print_empty_row = [&]()  { print_4col_row("", "", "", ""); };

  left_justify_output();
  // Show 3 decimal places for any floating point number
  show_n_decimal_places(PRECISION); 

  // Print customer's receipt
  puts("Customer Receipt");
  print_hline();
  print_col1("Customer"); print_col(NAME_FIELD, username); puts("");
  print_4col_row("Plant", "Quantity", "Cost ($)", "Stock Left");

  for (auto [type, item]: cart) {
    // TODO: Reduce code duplication with this
    int amount = item.quantity;
    const char* name = item.name;
    double cost = calc_cost(item);
    int stock_available = get_plant_choice(type)->quantity;
    print_4col_row(name, amount, cost, stock_available);
  }

  double subtotal = calc_subtotal_cost(cart);
  double total = calc_total_cost(subtotal);

  print_hline();
  print_2col_row("Cost", "Amount ($)");
  print_2col_row("Subtotal", subtotal);
  print_2col_row("Total", total);
  print_empty_row();

  // Show Loyalty Points
  Points points = calc_loyalty_points(cart);
  print_2col_row("Loyalty Points", points);

  ln();
  puts("Thank you! Please come again!");
}

int main(int argc, char** argv) {
  // Process command line arguments
  if ((argc < 2) || (argc > 2)) {
    puts("Error. Invalid number of arguments.");
    printf("Usage: %s [normal|loyalty|pretty-receipt]\n", argv[0]);
    puts("Please provide a mode to run the program.");
    puts("Available modes are: ");
    puts("\tnormal        : Part I of the assignment");
    puts("\tloyalty       : Part II of the assignment");
    puts("\tpretty-receipt: Part III of the assignment");
    return -1;
  }

  if (strequals(argv[1], "normal")) {
    // Part I:
    Cart cart = get_user_input();
    print_receipt(cart);
  } else if (strequals(argv[1], "loyalty")) {
    // Part II:
    std::string name = get_full_name();
    Cart cart = get_user_input();
    print_receipt(cart);
    show_loyalty_points(name.c_str(), cart);
  } else if (strequals(argv[1], "pretty-receipt")) {
    // Part III:
    std::string name = get_full_name();
    Cart cart = get_user_input();
    print_receipt_table(name.c_str(), cart);
  }
}
