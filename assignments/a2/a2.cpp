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
#include <limits>

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
typedef const char* Name;

typedef struct Item {
  Name name;
  Amount quantity;
  Price price;
} Item;

enum ITEM_ID {
  NONE,
  MONSTERA,
  PHILODENDRON,
  HOYA,
};

// Current Store Inventory
Item Monstera      = {"Monstera"    , 20, 11.50};
Item Philodendron  = {"Philodendron", 20, 13.75};
Item Hoya          = {"Hoya"        , 20, 10.99};

std::map<ITEM_ID, Item*> Inventory = {
  { MONSTERA, &Monstera },
  { PHILODENDRON, &Philodendron },
  { HOYA, &Hoya },
};

// Use a hashmap to bucket the items together
// We're going to batch the items together, and group alike items together in their respective buckets
// by summing their quantities together
typedef std::map<ITEM_ID, Item> Cart;

// General Purpose Functions

// Fast print newline
void ln() { puts(""); }

bool strequals(const char* s1, const char* s2) { return strcmp(s1, s2) == 0; }

// Clear input stream, and ignore any unparseable characters
void reset_stdin() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// The standard library still doesn't have a map.contains() method???
template <typename K, typename V>
bool hashmap_contains(const std::map<K, V> hashmap, const K key) {
  return (hashmap.find(key) != hashmap.end());
}

// Inventory Management Functions
ITEM_ID get_item_id(const char c) {
  switch(c) {
    case('M'): return MONSTERA;
    case('P'): return PHILODENDRON;
    case('H'): return HOYA;
    default: return NONE;
  }
}

Item* lookup_item(const ITEM_ID id) {
  return Inventory[id];
}

Cart add_to_cart(const ITEM_ID id, Item* plant, const Amount amount, Cart cart) {
  // Queue the purchase
  Item purchase = { plant->name, amount, plant->price };

  // Deduct the stock
  plant->quantity -= amount;
  
  // If we already have one of that item id in our bucket
  if (hashmap_contains(cart, id)) {
    // Just add the amounts together
    cart[id].quantity += amount;
  } else {
    // Add to cart
    cart[id] = purchase;
  }
  return cart;
}

// User Input Functions
void display_option(const char choice, const char* option) {
  const char choice_alt = toupper(choice);
  printf("\t[%c|%c] for %s\n", choice_alt, choice, option);
};

// Get user's selected option
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
    const ITEM_ID id = get_item_id(choice);
    const Item* item = lookup_item(id);
    ln();

    if (item == NULL) {
      // If the plant choice is invalid
      if (choice != 'A') {
        // If the user inputs multiple bad characters, we will ignore all of them
        reset_stdin();
        // Display an error 
        puts("Error: Invalid option selected");
      }
      continue; // And prompt the user again
    }

    // Get valid amount to purchase
    Amount amount;
    printf("How many %s pots would you like to buy?: ", item->name);
    std::cin >> amount;

    if (amount > item->quantity) {
      ln();
      puts("Sorry. There are not enough of this plant available in stock.");
      printf("Amount Available: %d\n", item->quantity);
      continue; // Return to prompt
    } 
    cart = add_to_cart(id, (Item*) item, amount, cart);
    ln();
  }
  return cart;
}

// Calculation Functions
Price calc_cost(const Item item) {
  return item.price * item.quantity;
}

// Sum the cost of the goods
Price calc_subtotal_cost(const Cart cart) {
  Price cost = 0;
  for (auto [_, item]: cart)
    cost += calc_cost(item);
  return cost;
}

// Apply PST and GST tax
Price calc_total_cost(const Price cost) {
  return cost + (cost * (GST + PST));
}

void print_greeting() {
  ln();
  puts("Thank you! Please come again!");
}

void print_receipt(const Cart cart) {
  auto print_plant_cost = [](const Amount amount, Name name, const Price cost) {
    printf("%d %s plants cost $%.*f\n", amount, name, PRECISION, cost);
  };

  // Print receipt
  puts("Units/Description/Cost of Items");
  for (auto [_, item]: cart) {
    Name name = item.name;
    const Amount amount = item.quantity;
    const Price cost = calc_cost(item);
    print_plant_cost(amount, name, cost);
  }

  const Price subtotal = calc_subtotal_cost(cart);
  const Price total = calc_total_cost(subtotal);

  printf("Total amount before tax is $%.*f\n", PRECISION, subtotal);
  printf("Total amount after tax is $%.*f\n", PRECISION, total);
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

Points calc_loyalty_points(const Price subtotal) {
  return round(subtotal / 0.75);
}

void show_loyalty_points(Name username, const Price subtotal) {
  const Points points = calc_loyalty_points(subtotal);
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
// Display customer's receipt in an aligned table
//
// NOTE:
// Keep in mind that a receipt is not very wide horizontally
// So we need to print this table longer vertically instead
void print_receipt_table(Name username, const Cart cart) {
  // Helper lambda functions for displaying the receipt in a table
  auto left_justify_output    = []() { std::cout << std::left; };
  auto right_justify_output   = []() { std::cout << std::right; };
  auto show_n_decimal_places  = [](const unsigned int n) { std::cout << std::fixed << std::setprecision(n); };
  auto set_fill_char          = [](const char c) { std::cout << std::setfill(c); };
  
  // Print columns
  auto print_col = [](int width, auto text) { std::cout << std::left << std::setw(width) << text; };
  auto print_col1 = [&](auto text) { print_col(COL_WIDTH[0], text); };
  auto print_col2 = [&](auto text) { print_col(COL_WIDTH[1], text); };
  auto print_col3 = [&](auto text) { print_col(COL_WIDTH[2], text); };
  auto print_col4 = [&](auto text) { print_col(COL_WIDTH[3], text); };

  // Print rows
  auto print_row_2cols = [&](auto col1, auto col2) { print_col1(col1); print_col2(col2); ln(); };
  auto print_row_4cols = [&](auto col1, auto col2, auto col3, auto col4)
    { print_col1(col1); print_col2(col2); print_col3(col3); print_col4(col4); ln(); };

  // Print horizontal line
  auto print_hline = [&]()      { set_fill_char('='); print_row_4cols("", "", "", ""); set_fill_char(' '); };
  auto print_empty_row = [&]()  { print_row_4cols("", "", "", ""); };

  // Setup output for table format
  left_justify_output();
  show_n_decimal_places(PRECISION); 

  // Display the customer's receipt

  // Print receipt header
  puts("Customer Receipt");
  print_hline();
  print_row_2cols("Customer", username);

  // Print receipt body
  print_row_4cols("Item", "Quantity", "Cost ($)", "Stock Left");
  for (auto [id, item]: cart) {
    Name name = item.name;
    const Amount amount = item.quantity;
    const Price cost = calc_cost(item);
    const Amount stock_available = lookup_item(id)->quantity;
    print_row_4cols(name, amount, cost, stock_available);
  }
  print_hline();

  // Print total price
  const Price subtotal = calc_subtotal_cost(cart);
  const Price total = calc_total_cost(subtotal);

  print_row_2cols("Cost", "Amount ($)");
  print_row_2cols("Subtotal", subtotal);
  print_row_2cols("Total", total);
  print_empty_row();

  // Show Loyalty Points
  const Points points = calc_loyalty_points(subtotal);
  print_row_2cols("Loyalty Points", points);
}

int main(int argc, char** argv) {
  // Process command line arguments
  if ((argc < 2) || (argc > 2)) {
    puts("Error. Invalid number of arguments.");
    puts("Please provide a mode to run the program.");
    puts("Available modes are: ");
    puts("\tnormal        : Part I of the assignment");
    puts("\tloyalty       : Part II of the assignment");
    puts("\tpretty-receipt: Part III of the assignment");
    printf("Usage: %s [normal|loyalty|pretty-receipt]\n", argv[0]);
    return -1;
  }

  if (strequals(argv[1], "normal")) {
    // Part I:
    const Cart cart = get_user_input();
    print_receipt(cart);
  } else if (strequals(argv[1], "loyalty")) {
    // Part II:
    const std::string name = get_full_name();
    const Cart cart = get_user_input();
    const Price subtotal = calc_subtotal_cost(cart);
    print_receipt(cart);
    show_loyalty_points(name.c_str(), subtotal);
  } else if (strequals(argv[1], "pretty-receipt")) {
    // Part III:
    const std::string name = get_full_name();
    const Cart cart = get_user_input();
    print_receipt_table(name.c_str(), cart);
  }
  print_greeting();
  return 0;
}
