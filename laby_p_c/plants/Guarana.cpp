#include "Guarana.h"

Guarana::Guarana(World* world, std::pair<int, int> pos)
	: Plant(world, pos)
{
}

Guarana::~Guarana()
{
}

void Guarana::handleCollision(Organism* other)
{
	other->setStrength(other->getStrength() + STRENGTH_INCREMENT);
	Plant::handleCollision(other);
}

void Guarana::draw()
{
	world->console->backgroundColor(LIGHTBLUE);
	std::cout << "G";
}

std::string Guarana::getType() const
{
	return "Guarana";
}
