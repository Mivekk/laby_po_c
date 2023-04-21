#include "Animal.h"
#include "animals/Wolf.h"
#include "animals/Sheep.h"

Animal::Animal(World* world, std::pair<int, int> pos)
	: Organism(world), skipMove(false), didMove(false)
{
	this->pos = pos;
	world->board[pos.second][pos.first] = this;
}

Animal::~Animal()
{
}

void Animal::update()
{
	// increment age every turn
	age++;

	didMove = false;

	// skip movement
	if (skipMove) {
		skipMove = false;
		return;
	}

	// move animal
	std::pair<int, int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	std::pair<int, int> randomDirection = directions[rand() % 4];

	std::pair<int, int> afterPos = { this->pos.first + randomDirection.first, this->pos.second + randomDirection.second };

	if (afterPos.first >= world->board[0].size() ||
		afterPos.first < 0) {

		afterPos.first = this->pos.first - randomDirection.first;
	}
	else if (afterPos.second >= world->board.size() ||
		afterPos.second < 0) {

		afterPos.second = this->pos.second - randomDirection.second;
	}

	// space is occupied -> collision
	if (world->board[afterPos.second][afterPos.first]) {
		handleCollision(world->board[afterPos.second][afterPos.first]);
	}
	else {
		world->board[pos.second][pos.first] = nullptr;

		this->pos.first = afterPos.first;
		this->pos.second = afterPos.second;

		world->board[pos.second][pos.first] = this;
	}

	didMove = true;
}

void Animal::handleCollision(Organism* other)
{
	// animals are the same
	if (typeid(*this) == typeid(*other)) {
		breed((Animal*)other);
	}
	else {
		fight(other);
	}
}

void Animal::draw()
{
	console.backgroundColor(RED);
	std::cout << ".";
}

void Animal::breed(Animal* animal)
{
	std::pair<int, int> newPos = findFreeSpace(pos, animal->getPos());

	if (newPos.first != -1) {
		Animal* newAnimal = nullptr;

		if (typeid(*this) == typeid(Wolf)) {
			newAnimal = new Wolf(world, newPos);
		}
		else if (typeid(*this) == typeid(Sheep)) {
			newAnimal = new Sheep(world, newPos);
		}

		try {
			if (newAnimal == nullptr) {
				throw("Unknown animal");
			}
			world->organisms.push_back(newAnimal);
		}
		catch (const std::string& exception) {
			console.write(30, 10);
			std::cerr << exception;
		}
	}

	if (!animal->didMove) {
		animal->skipMove = true;
	}
}

void Animal::fight(Organism* organism)
{
	if (strength > organism->getStrength()) {
		world->board[pos.second][pos.first] = nullptr;
		world->board[organism->getPos().second][organism->getPos().first] = this;
		world->removeOrganism(organism);
	}
	else if (strength < organism->getStrength()) {
		world->board[organism->getPos().second][organism->getPos().first] = nullptr;
		world->board[pos.second][pos.first] = organism;
		world->removeOrganism(this);
	}
	else {

	}
}

std::pair<int, int> Animal::findFreeSpace(std::pair<int, int> pos1, std::pair<int, int> pos2)
{
	std::pair<int, int> directions[] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	std::pair<int, int> freePos = { -1, -1 };
	for (const auto& dir : directions) {
		std::pair<int, int> afterPos = { pos1.first + dir.first, pos1.second + dir.second };

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

		afterPos = { pos2.first + dir.first, pos2.second + dir.second };

		if (afterPos.first >= world->board[0].size() ||
			afterPos.first < 0 || afterPos.second < 0 ||
			afterPos.second >= world->board.size()) {

			continue;
		}

		space = world->board[afterPos.second][afterPos.first];
		if (space == nullptr) {
			freePos = { afterPos.first, afterPos.second };
			break;
		}
	}

	return freePos;
}
