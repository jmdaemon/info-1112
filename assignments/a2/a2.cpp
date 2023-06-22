#include <iostream>
#include <iomanip>
#include <tuple>
#include <cstdio>
#include <vector>

// Part I
typedef unsigned int Amount;
typedef double Price;

// Taxes

// Tax amounts in B.C
const double PST = 0.07;
const double GST = 0.05;

// Plants
enum PLANT_TYPE {
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

typedef struct Plant {
  const char* name;
  Amount stock;
  Price price;
} Plant;

// Make const/nonconst
Plant None          = {NULL, 0, 0};
Plant Monstera      = {"Monstera"     , PLANT_STOCK[0], PLANT_PRICES[0]};
Plant Philodendron  = {"Philodendron" , PLANT_STOCK[1], PLANT_PRICES[1]};
Plant Hoya          = {"Hoya"         , PLANT_STOCK[2], PLANT_PRICES[2]};

typedef std::vector<Plant> Cart;

Plant get_plant_choice(char c) {
  switch(c) {
    case('M'): return Monstera;
    case('P'): return Philodendron;
    case('H'): return Hoya;
    default:
       return None;
  }
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

    Plant plant = get_plant_choice(choice);
    // If the plant choice is invalid, we will output an error and prompt the user again
    if (&plant == &None) {
      if (choice == 'A') {
        continue;
      } else {
        puts("Error: Invalid plant selected");
        break;
      }
    }
    
    int amount;
    printf("How many %s pots would you like to buy?: ", plant.name);
    std::cin >> amount;

    Plant purchase;
    if (amount > plant.stock) {
      puts("Sorry. There are not enough of this plant available in stock.");
      printf("Amount Available: %d\n", plant.stock);
    } else {
      // Deduct the stock
      plant.stock -= amount;
      // Queue the purchase
      purchase.price = plant.price;
      purchase.stock = amount;
    }
    // Add to cart
    cart.push_back(purchase);
  }
  return cart;
}

double calc_cost(Plant plant, int amount) {
  return (plant.price * amount);
}

// Sum the cost of the goods
double calc_subtotal_cost(Cart cart) {
  double cost = 0;
  for (auto item: cart) {
    cost += (item.price * item.stock);
  }
  return cost;
}

// Apply taxes
double calc_total_cost(double cost) {
  return cost * (GST + PST);
}

void print_receipt(Cart cart) {
  //const char* amount_format = "$%.3f";
  const unsigned int PRECISION = 3;

  //std::cout << std::fixed << std::setprecision(PRECISION);
  puts("Units/Description/Cost of Items");

  auto print_plant_cost = [&](int amount, const char* name, double cost) {
    printf("%d %s plants cost $%.*f\n", amount, name, PRECISION, cost);
  };

  // Print receipt
  for (auto plant: cart) {
    int amount = plant.stock;
    const char* name = plant.name;
    double cost = calc_cost(plant, amount);
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
