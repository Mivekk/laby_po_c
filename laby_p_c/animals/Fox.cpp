#include "Fox.h"

Fox::Fox(World* world, std::pair<int, int> pos)
	: Animal(world, pos)
{
	strength = 3;
	initiative = 7;
}

Fox::~Fox()
{
}

std::pair<int, int> Fox::getNextPos()
{
	std::pair<int, int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	int randomNumber = rand() % 4;
	std::pair<int, int> randomDirection;
	std::pair<int, int> afterPos;

	int curI = 0, maxI = 4;
	do {
		randomDirection = directions[randomNumber];

		afterPos = { pos.first + randomDirection.first, pos.second + randomDirection.second };

		if (afterPos.first >= world->board[0].size() ||
			afterPos.first < 0) {

			afterPos.first = pos.first - randomDirection.first;
		}
		else if (afterPos.second >= world->board.size() ||
			afterPos.second < 0) {

			afterPos.second = pos.second - randomDirection.second;
		}
		curI++;
	} 
	while (world->board[afterPos.second][afterPos.first] != nullptr && curI <= maxI &&
		world->board[afterPos.second][afterPos.first]->getStrength() > strength);

	if (curI > maxI) {
		return pos;
	}

	return afterPos;
}

void Fox::draw()
{
	world->console->backgroundColor(BROWN);
	std::cout << "F";
}

std::string Fox::getType() const
{
	return "Fox";
}
