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
	world->console->backgroundColor(DARKGRAY);
	std::cout << "W";
}

std::string Wolf::getType() const
{
	return "Wolf";
}
