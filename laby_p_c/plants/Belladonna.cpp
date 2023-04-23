#include "Belladonna.h"

Belladonna::Belladonna(World* world, std::pair<int, int> pos)
	: Plant(world, pos)
{
	strength = 99;
}

Belladonna::~Belladonna()
{
}

void Belladonna::handleCollision(Organism* other)
{
	world->board[other->getPos().second][other->getPos().first] = nullptr;
	world->removeOrganism(other);
}

void Belladonna::draw()
{
	world->console->backgroundColor(RED);
	std::cout << "B";
}

std::string Belladonna::getType() const
{
	return "Belladonna";
}
