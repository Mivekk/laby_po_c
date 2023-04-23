#include "Organism.h"

Organism::Organism(World* world)
	: world(world), strength(0), initiative(0), age(0), pos{ 0, 0 }
{
}

Organism::~Organism()
{
}

void Organism::setStrength(int newStrength)
{
	strength = newStrength;
}

void Organism::setInitiative(int newInitiative)
{
	initiative = newInitiative;
}

void Organism::setAge(int newAge)
{
	age = newAge;
}

void Organism::setPos(std::pair<int, int> newPos)
{
	pos = newPos;
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

std::pair<int, int> Organism::getNextPos()
{
	std::pair<int, int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	std::pair<int, int> randomDirection = directions[rand() % 4];

	std::pair<int, int> afterPos = { pos.first + randomDirection.first, pos.second + randomDirection.second };

	if (afterPos.first >= world->board[0].size() ||
		afterPos.first < 0) {

		afterPos.first = pos.first - randomDirection.first;
	}
	else if (afterPos.second >= world->board.size() ||
		afterPos.second < 0) {

		afterPos.second = pos.second - randomDirection.second;
	}

	return afterPos;
}

std::pair<int, int> Organism::findFreeSpace(std::pair<int, int> startPos)
{
	std::pair<int, int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	std::pair<int, int> freePos = { -1, -1 };

	for (const auto& dir : directions) {
		std::pair<int, int> afterPos = { startPos.first + dir.first, startPos.second + dir.second };

		if (afterPos.first >= world->board[0].size() ||
			afterPos.first < 0 || afterPos.second < 0 ||
			afterPos.second >= world->board.size()) {

			continue;
		}

		Organism* space = world->board[afterPos.second][afterPos.first];
		if (space == nullptr) {
			freePos = { afterPos.first, afterPos.second };
			break;
		}
	}

	return freePos;
}