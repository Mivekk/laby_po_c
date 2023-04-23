#include "Plant.h"
#include "plants/Grass.h"
#include "plants/Dandelion.h"
#include "plants/Guarana.h"
#include "plants/Belladonna.h"
#include "plants/Sosnowsky.h"

Plant::Plant(World* world, std::pair<int, int> pos)
	: Organism(world), didRegrow(false)
{
	this->pos = pos;
	world->board[pos.second][pos.first] = this;
}

Plant::~Plant()
{
}

void Plant::update()
{
	int regrow = rand() % 100;
	if (regrow < REGROW_CHANCE && !didRegrow) {
		std::pair<int, int> newPos = getNextPos();

		Organism* organism = world->board[newPos.second][newPos.first];
		if (organism != nullptr && dynamic_cast<Plant*>(organism) != nullptr) {
			world->board[organism->getPos().second][organism->getPos().first] = nullptr;
			world->removeOrganism(organism);
		}
		else if (organism != nullptr && dynamic_cast<Plant*>(organism) == nullptr) {
			return;
		}

		Plant* newPlant = nullptr;
		std::string log;

		if (typeid(*this) == typeid(Grass)) {
			log = "Grass";
			newPlant = new Grass(world, newPos);
		}
		else if (typeid(*this) == typeid(Dandelion)) {
			log = "Dandelion";
			newPlant = new Dandelion(world, newPos);
		}
		else if (typeid(*this) == typeid(Guarana)) {
			log = "Guarana";
			newPlant = new Guarana(world, newPos);
		}
		else if (typeid(*this) == typeid(Belladonna)) {
			log = "Belladonna";
			newPlant = new Belladonna(world, newPos);
		}
		else if (typeid(*this) == typeid(Sosnowsky)) {
			log = "Sosnowsky";
			newPlant = new Sosnowsky(world, newPos);
		}

		if (newPlant == nullptr) {
			return;
		}

		log = log + " grows at X: " + std::to_string(newPos.first)
			+ ", Y: " + std::to_string(newPos.second);
		world->console->addLog(log);
		world->addOrganism(newPlant);

		newPlant->didRegrow = true;
		didRegrow = true;

		return;
	}

	didRegrow = false;
}

void Plant::handleCollision(Organism* other)
{
	world->board[other->getPos().second][other->getPos().first] = nullptr;
	world->removeOrganism(this);
}