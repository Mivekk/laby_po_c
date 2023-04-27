#include "World.h"

int main() {
	srand((unsigned int)time(NULL));

	std::cout << "Podaj rozmiar planszy: \n";
	int sizeX, sizeY;
	std::cin >> sizeX >> sizeY;

	World world({ sizeX, sizeY });

	return 0;
}