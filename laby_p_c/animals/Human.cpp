#include "Human.h"

Human::Human(World* world, std::pair<int, int> pos)
	: Animal(world, pos), abilityCooldown(-1), abilityDuration(-1), abilityActivated(false), nextMove(0)
{
	strength = 5;
	initiative = 4;
}

Human::~Human()
{
}

std::pair<int, int> Human::getNextPos()
{
	std::pair<int, int> afterPos = pos;

	switch (nextMove) {
	case ARROW_UP:
		afterPos.second--;

		if (useAbility()) {
			afterPos.second--;
		}
		break;
	case ARROW_DOWN:
		afterPos.second++;

		if (useAbility()) {
			afterPos.second++;
		}
		break;
	case ARROW_RIGHT:
		afterPos.first++;

		if (useAbility()) {
			afterPos.first++;
		}
		break;
	case ARROW_LEFT:
		afterPos.first--;

		if (useAbility()) {
			afterPos.first--;
		}
		break;
	}

	nextMove = NULL;

	if (afterPos.first < world->board[0].size() &&
		afterPos.first >= 0 && afterPos.second >= 0 &&
		afterPos.second < world->board.size()) {

		std::string log = "Human moves to X: " + std::to_string(afterPos.first) 
			+ ", Y: " + std::to_string(afterPos.second);
		if (afterPos != pos) {
			world->console->addLog(log);
		}
		
		return afterPos;
	}

	return pos;
}

void Human::draw()
{
	world->console->backgroundColor(BLACK);
	std::cout << "H";
}

std::string Human::getType() const
{
	return "Human";
}

bool Human::useAbility()
{
	if (abilityDuration > 0) {
		if (abilityDuration < 2) {
			if (rand() % 2) {
				return true;
			}
		}
		else {
			return true;
		}
	}

	return false;
}

void Human::setNextMove(int arrowCode)
{
	nextMove = arrowCode;
}
