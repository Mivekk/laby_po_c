#include "Dandelion.h"

Dandelion::Dandelion(World* world, std::pair<int, int> pos)
	: Plant(world, pos)
{
}

Dandelion::~Dandelion()
{
}

void Dandelion::update()
{
	for (int i = 0; i < REGROW_TRIES; i++) {
		Plant::update();
	}
}

void Dandelion::draw()
{
	world->console->backgroundColor(YELLOW);
	std::cout << "D";
}

std::string Dandelion::getType() const
{
	return "Dandelion";
}
