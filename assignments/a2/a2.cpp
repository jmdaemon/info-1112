#include <iostream>
#include <iomanip>
#include <tuple>
#include <cstdio>
#include <vector>
#include <map>

// Part I
typedef unsigned int Amount;
typedef double Price;

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
//Plant None          = {NONE, "", 0, 0};
Plant Monstera      = {MONSTERA     , "Monstera"    , PLANT_STOCK[0], PLANT_PRICES[0]};
Plant Philodendron  = {PHILODENDRON , "Philodendron", PLANT_STOCK[1], PLANT_PRICES[1]};
Plant Hoya          = {HOYA         , "Hoya"        , PLANT_STOCK[2], PLANT_PRICES[2]};

typedef std::map<PLANT_TYPE, Item> Cart;

Plant* get_plant_choice(char c) {
  Plant* result = NULL;
  switch(c) {
    case('M'): result = &Monstera; break;
    case('P'): result = &Philodendron; break;
    case('H'): result = &Hoya; break;
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
  while(choice != 'A') {
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
      //Plant purchase = { plant->type, Item { item.name, amount, item.price }};
      Item purchase = { item.name, amount, item.price };

      // Deduct the stock
      item.quantity -= amount;
      
      if (found_in_hashmap(cart, plant->type)) {
        //cart.at(plant->type).quantity += amount;
        cart[plant->type].quantity += amount;
      } else {
        // Add to cart
        //cart.push_back(purchase);
        //cart.insert({ plant->type, purchase });
        cart[plant->type] = purchase;
      }
    }
    puts("");
  }
  return cart;
}

//Cart batch_cart(Cart cart) {
  //for (auto purchase: cart) {
    //switch(purchase.type) {
      //case(MONSTERA): 
    //}
  //}
//}

// Calculation
double calc_cost(Item item) {
  return (item.price * item.quantity);
}

// Sum the cost of the goods
double calc_subtotal_cost(Cart cart) {
  double cost = 0;
  for (auto [_, item]: cart) {
    //Item item = plant.item;
    cost += calc_cost(item);
  }
  return cost;
}

// Apply PST and GST tax
double calc_total_cost(double cost) {
  return cost += (cost * (GST + PST));
}

void print_receipt(Cart cart) {
  const unsigned int PRECISION = 3;

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

  //std::cout << "Total amount before tax is $" << subtotal << std::endl;
  //std::cout << "Total amount after tax is $" << total << std::endl;
  //printf("Total amount before tax is %s", printf(amount_format, subtotal));
  //printf("Total amount after tax is %s", printf(amount_format, total));
  
  puts("");
  puts("Thank you! Please come again!");
}



// Part II
// Part III

int main() {
  Cart cart = get_user_input();
  //Cart cart = {};
  print_receipt(cart);
}
