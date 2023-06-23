/**
  * Student Name    : Joseph Diza
  * Student Number  : 100427500
  * Course Name     : INFO 1112 S10
  **/

#include <iostream>
#include <iomanip>
#include <tuple>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <map>

// Part I: Tom's Nursery Shop
typedef unsigned int Amount;
typedef double Price;

// Constants
const unsigned int PRECISION = 3;

// Taxes
// Tax amounts in B.C
const double PST = 0.07;
const double GST = 0.05;

// Program Variants
enum PLANT_TYPE {
  NONE,
  MONSTERA,
  PHILODENDRON,
  HOYA,
};

const Amount PLANT_STOCK[3] = {
  20,
  20,
  20,
};

const double PLANT_PRICES[3] = {
  11.50,
  13.75,
  10.99,
};

typedef struct Item {
  const char* name;
  Amount quantity;
  Price price;
} Item;

typedef struct Plant {
  PLANT_TYPE type;
  Item item;
} Plant;

// Make const/nonconst
Plant Monstera      = {MONSTERA     , "Monstera"    , PLANT_STOCK[0], PLANT_PRICES[0]};
Plant Philodendron  = {PHILODENDRON , "Philodendron", PLANT_STOCK[1], PLANT_PRICES[1]};
Plant Hoya          = {HOYA         , "Hoya"        , PLANT_STOCK[2], PLANT_PRICES[2]};

typedef std::map<PLANT_TYPE, Item> Cart;

bool strequals(const char* s1, const char* s2) {
  return (strcmp(s1, s2) == 0);
}

Plant* get_plant_choice(char c) {
  Plant* result = NULL;
  switch(c) {
    case('M'): result = &Monstera; break;
    case('P'): result = &Philodendron; break;
    case('H'): result = &Hoya; break;
  }
  return result;
}

Plant* get_plant_choice_type(PLANT_TYPE type) {
  Plant* result = NULL;
  switch(type) {
    case(MONSTERA): result = &Monstera; break;
    case(PHILODENDRON): result = &Philodendron; break;
    case(HOYA): result = &Hoya; break;
    default: result = NULL;
  }
  return result;
}

template <typename K, typename V>
bool found_in_hashmap(std::map<K, V> hashmap, K key) {
  return (hashmap.find(key) != hashmap.end());
}

auto get_user_input() {
  auto display_option = [](char choice, const char* option) {
    char choice_alt = toupper(choice);
    printf("\t[%c|%c] for %s\n", choice_alt, choice, option);
  };

  char choice;
  Cart cart;

  puts("Welcome to Tom's Nursery Shop");
  while (choice != 'A') {
    puts("Select from our plants below or checkout: ");
    display_option('m', "Monstera");
    display_option('p', "Philodendron");
    display_option('h', "Hoya");
    display_option('a', "Checkout");
    printf("Select: ");
    std::cin >> choice;
    choice = toupper(choice);

    Plant* plant = get_plant_choice(choice);
    // If the plant choice is invalid, we will output an error and prompt the user again
    if (plant == NULL) {
      if (choice != 'A') {
        puts("");
        puts("Error: Invalid plant selected");
      }
      continue; // Return to prompt
    }

    Item item = plant->item;
    Amount amount;
    printf("How many %s pots would you like to buy?: ", item.name);
    std::cin >> amount;

    if (amount > item.quantity) {
      puts("");
      puts("Sorry. There are not enough of this plant available in stock.");
      printf("Amount Available: %d\n", item.quantity);
    } else {
      // Queue the purchase
      Item purchase = { item.name, amount, item.price };

      // Deduct the stock
      item.quantity -= amount;
      
      if (found_in_hashmap(cart, plant->type)) {
        cart[plant->type].quantity += amount;
      } else {
        // Add to cart
        cart[plant->type] = purchase;
      }
    }
    puts("");
  }
  return cart;
}

// Calculation
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
  
  puts("");
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
const unsigned int COL1_WIDTH = 16;
const unsigned int COL2_WIDTH = 10;
const unsigned int COL3_WIDTH = 10;
const unsigned int COL4_WIDTH = 8;
const unsigned int NAME_FIELD = COL1_WIDTH * 4;

// Prints a receipt in the following format:
// Customer       [name]
// Plant          Amount      Cost      Stock Left
// Monsterra      [amount]    [cost]    [plant.quantity]
// Philodendron   [amount]    [cost]    [plant.quantity]
// Hoya           [amount]    [cost]    [plant.quantity]
// Subtotal       [subtotal]
// Total          [total]
// Loyalty Points [points]
void print_receipt_table(const char* username, Cart cart) {
  // Helper functions for displaying the receipt in a table
  auto left_justify_output   = []() { std::cout << std::left; };
  auto show_n_decimal_places = [](unsigned int n) { std::cout << std::fixed << std::setprecision(n); };
  
  // Print columns
  auto print_col = [](int width, auto text)
    { std::cout << std::left << std::setw(width) << text; };
  auto print_col1 = [&](auto text) { print_col(COL1_WIDTH, text); };
  auto print_col2 = [&](auto text) { print_col(COL2_WIDTH, text); };
  auto print_col3 = [&](auto text) { print_col(COL3_WIDTH, text); };
  auto print_col4 = [&](auto text) { print_col(COL4_WIDTH, text); };

  // Print rows
  auto print_2col_row = [&](auto col1, auto col2)
    { print_col1(col1); print_col2(col2); puts(""); };
  auto print_4col_row = [&](auto col1, auto col2, auto col3, auto col4) {
    print_col1(col1); print_col2(col2);
    print_col3(col3); print_col4(col4); puts("");
  };

  // Print horizontal line
  auto print_hline = [&]() {
    std::cout << std::setfill('=');
    print_4col_row("", "", "", "");
    std::cout << std::setfill(' ');
  };

  left_justify_output();
  // Show 3 decimal places for any floating point number
  show_n_decimal_places(PRECISION); 

  puts("Customer Receipt");
  print_hline();
  print_col1("Customer"); print_col(COL1_WIDTH * 4, username); puts("");
  print_4col_row("Plant", "Amount", "Cost", "Stock Left");
  for (auto [type, item]: cart) {
    int amount = item.quantity;
    const char* name = item.name;
    double cost = calc_cost(item);
    int stock_available = get_plant_choice_type(type)->item.quantity;
    print_4col_row(name, amount, cost, stock_available);
  }
  double subtotal = calc_subtotal_cost(cart);
  double total = calc_total_cost(subtotal);

  print_hline();
  print_2col_row("Subtotal", subtotal);
  print_2col_row("Total", total);

  puts("");
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
