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
	if (!didRegrow) {
		for (int i = 0; i < REGROW_TRIES; i++) {
			int regrow = rand() % 100;
			if (regrow < REGROW_CHANCE) {
				std::pair<int, int> newPos = getNextPos();

				Organism* organism = world->board[newPos.second][newPos.first];
				if (organism != nullptr && dynamic_cast<Plant*>(organism) != nullptr) {
					world->board[organism->getPos().second][organism->getPos().first] = nullptr;
					world->removeOrganism(organism);
				}
				else if (organism != nullptr && dynamic_cast<Plant*>(organism) == nullptr) {
					return;
				}

				Dandelion* newPlant = new Dandelion(world, newPos);

				std::string log = "Dandelion grows at X: " + std::to_string(newPos.first)
					+ ", Y: " + std::to_string(newPos.second);
				world->console->addLog(log);
				world->addOrganism(newPlant);

				newPlant->didRegrow = true;
				didRegrow = true;
			}
		}
		return;
	}

	didRegrow = false;
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
