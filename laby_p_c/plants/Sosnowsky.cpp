#include "Sosnowsky.h"

Sosnowsky::Sosnowsky(World* world, std::pair<int, int> pos)
	: Plant(world, pos)
{
}

Sosnowsky::~Sosnowsky()
{
}

void Sosnowsky::update()
{
	Plant::update();

	std::pair<int, int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	for (const auto& dir : directions) {
		std::pair<int, int> afterPos = { pos.first + dir.first, pos.second + dir.second };

		if (afterPos.first >= world->board[0].size() ||
			afterPos.first < 0 || afterPos.second < 0 ||
			afterPos.second >= world->board.size()) {

			continue;
		}

		Organism* space = world->board[afterPos.second][afterPos.first];

		if (space != nullptr && dynamic_cast<Plant*>(space) == nullptr) {
			handleCollision(space);
		}
	}
}

void Sosnowsky::handleCollision(Organism* other)
{
	world->board[other->getPos().second][other->getPos().first] = nullptr;
	world->removeOrganism(other);
}

void Sosnowsky::draw()
{
	world->console->backgroundColor(LIGHTRED);
	std::cout << "S";
}

std::string Sosnowsky::getType() const
{
	return "Sosnowsky";
}