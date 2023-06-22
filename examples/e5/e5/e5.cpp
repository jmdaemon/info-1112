#include <iostream>
#include <ctime>

int gen_random_number(int min, int max) {
	return (rand() % (max - min + 1) + min);
}

int main() {
	srand(time(NULL)); // Set the random seed
	int random_number = gen_random_number(1, 6);
	printf("Random Number Generated: %d", random_number);
	return 0;
}