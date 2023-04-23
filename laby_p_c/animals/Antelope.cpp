#include "Antelope.h"

Antelope::Antelope(World* world, std::pair<int, int> pos)
	: Animal(world, pos)
{
	strength = 4;
	initiative = 4;
}

Antelope::~Antelope()
{
}

std::pair<int, int> Antelope::getNextPos()
{
	std::pair<int, int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
										 { 2, 0 }, { -2, 0 }, { 0, 2 }, { 0, -2 } };

	std::pair<int, int> randomDirection = directions[rand() % 8];

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

void Antelope::draw()
{
	world->console->backgroundColor(LIGHTCYAN);
	std::cout << "A";
}

bool Antelope::escaped()
{
	int escapes = rand() % 100;
	if (escapes < ESCAPE_CHANCE) {
		return false;
	}

	// find free space and go there
	std::pair<int, int> afterPos = findFreeSpace(pos);

	if (afterPos.first != -1) {
		move(afterPos);
	}
	else {
		world->board[pos.second][pos.first] = nullptr;
		world->removeOrganism(this);
	}

	return true;
}

std::string Antelope::getType() const
{
	return "Antelope";
}
