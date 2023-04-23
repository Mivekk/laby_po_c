#include "Animal.h"
#include "animals/Wolf.h"
#include "animals/Sheep.h"
#include "animals/Fox.h"
#include "animals/Turtle.h"
#include "animals/Antelope.h"

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
	std::pair<int, int> afterPos = getNextPos();

	// space is occupied -> collision
	if (world->board[afterPos.second][afterPos.first] && pos != afterPos) {
		handleCollision(world->board[afterPos.second][afterPos.first]);
	}
	else {
		move(afterPos);
	}

	didMove = true;
}

void Animal::handleCollision(Organism* other)
{
	// animals are the same
	if (typeid(*this) == typeid(*other)) {
		breed((Animal*)other);
	}
	else if (dynamic_cast<Animal*>(other)) {
		fight(other);
	}
	else if (other != nullptr) {
		std::pair<int, int> afterPos = { other->getPos().first, other->getPos().second };

		other->handleCollision(this);

		if (pos.first >= 0) {
			move(afterPos);
		}
	}
}

bool Animal::bounceAttack(Organism* organism)
{
	return false;
}

bool Animal::escaped()
{
	return false;
}

void Animal::breed(Animal* animal)
{
	std::pair<int, int> newPos = findFreeSpace(pos);
	if (newPos.first == -1) {
		newPos = findFreeSpace(animal->getPos());
	}

	if (newPos.first != -1) {
		Animal* newAnimal = nullptr;
		std::string log;

		if (typeid(*this) == typeid(Wolf)) {
			log = "Wolf";
			newAnimal = new Wolf(world, newPos);
		}
		else if (typeid(*this) == typeid(Sheep)) {
			log = "Sheep";
			newAnimal = new Sheep(world, newPos);
		}
		else if (typeid(*this) == typeid(Fox)) {
			log = "Fox";
			newAnimal = new Fox(world, newPos);
		}
		else if (typeid(*this) == typeid(Turtle)) {
			log = "Turtle";
			newAnimal = new Turtle(world, newPos);
		}
		else if (typeid(*this) == typeid(Antelope)) {
			log = "Antelope";
			newAnimal = new Antelope(world, newPos);
		}

		log = log + " spawns at X: " + std::to_string(newPos.first)
			+ ", Y: " + std::to_string(newPos.second);

		try {
			if (newAnimal == nullptr) {
				throw("Unknown animal");
			}

			world->console->addLog(log);
			world->addOrganism(newAnimal);
		}
		catch (const std::string& exception) {
			world->console->setup(30, 10);
			std::cerr << exception;
		}
	}

	if (!animal->didMove) {
		animal->skipMove = true;
	}
}

void Animal::fight(Organism* organism)
{
	std::string log;
	if (organism->bounceAttack(this)) {
		log = organism->getType() + " bounces attack from " + getType();
	}
	else if (strength >= organism->getStrength()) {
		std::pair<int, int> afterPos = { organism->getPos().first, organism->getPos().second };


		if (organism->escaped()) {
			if (organism != nullptr && organism->getPos().first > 0) {
				log = organism->getType() + " escapes from " + getType();

				world->console->addLog(log);
			}

			move(afterPos);
			return;
		}

		log = getType() + " eats " + organism->getType() + " at X: " + 
			std::to_string(afterPos.first) + ", Y: " + std::to_string(afterPos.second);
 
		world->console->addLog(log);

		world->board[afterPos.second][afterPos.first] = nullptr;
		world->removeOrganism(organism);

		move(afterPos);
	}
	else if (strength < organism->getStrength()) {
		log = organism->getType() + " eats " + getType() + " at X: " +
			std::to_string(pos.first) + ", Y: " + std::to_string(pos.second);

		world->console->addLog(log);

		world->board[pos.second][pos.first] = nullptr;
		world->removeOrganism(this);
	}
}

void Animal::move(std::pair<int, int> dest)
{
	world->board[pos.second][pos.first] = nullptr;

	pos.first = dest.first;
	pos.second = dest.second;

	world->board[pos.second][pos.first] = this;
}

