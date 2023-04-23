#include "Grass.h"

Grass::Grass(World* world, std::pair<int, int> pos)
	: Plant(world, pos)
{
}

Grass::~Grass()
{
}

void Grass::draw()
{
	world->console->backgroundColor(LIGHTGREEN);
	std::cout << "G";
}

std::string Grass::getType() const
{
	return "Grass";
}
