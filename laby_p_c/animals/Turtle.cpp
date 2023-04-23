#include "Turtle.h"

Turtle::Turtle(World* world, std::pair<int, int> pos)
    : Animal(world, pos)
{
    strength = 2;
    initiative = 1;
}

Turtle::~Turtle()
{
}

std::pair<int, int> Turtle::getNextPos()
{
    int moves = rand() % 100;
    if (moves >= MOVE_CHANCE) {
        return pos;
    }

    std::pair<int, int> afterPos = Animal::getNextPos();

	return afterPos;
}

void Turtle::draw()
{
    world->console->backgroundColor(GREEN);
    std::cout << "T";
}

bool Turtle::bounceAttack(Organism* organism)
{
    return organism->getStrength() < 5;
}

std::string Turtle::getType() const
{
    return "Turtle";
}
