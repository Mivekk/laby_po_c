#include "Wolf.h"

Wolf::Wolf(World* world, std::pair<int, int> pos)
	: Animal(world, pos) 
{
	strength = 9;
	initiative = 5;
}

Wolf::~Wolf()
{
}

void Wolf::draw()
{
	console.backgroundColor(DARKGRAY);
	std::cout << "W";
}
