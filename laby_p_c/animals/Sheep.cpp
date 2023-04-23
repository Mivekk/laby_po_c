#include "Sheep.h"

Sheep::Sheep(World* world, std::pair<int, int> pos)
	: Animal(world, pos)
{
	strength = 4;
	initiative = 4;
}

Sheep::~Sheep()
{
}

void Sheep::draw()
{
	world->console->backgroundColor(LIGHTGRAY);
	std::cout << "S";
}

std::string Sheep::getType() const
{
	return "Sheep";
}
