#include "Organism.h"

Organism::Organism(World* world)
	: world(world), strength(0), initiative(0), age(0), pos{ 0, 0 }
{
}

Organism::~Organism()
{
}

int Organism::getStrength() const
{
	return strength;
}

int Organism::getInitiative() const
{
	return initiative;
}

int Organism::getAge() const
{
	return age;
}

std::pair<int, int> Organism::getPos() const
{
	return pos;
}
