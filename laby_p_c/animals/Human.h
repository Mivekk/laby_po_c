#pragma once
#include "../Animal.h"

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

class Human : public Animal
{
public:
	Human(World* world, std::pair<int, int> pos);
	~Human();

	void setNextMove(int arrowCode);

	int abilityCooldown;
	int abilityDuration;
	bool abilityActivated;

private:
	std::pair<int, int> getNextPos() override;
	void draw() override;

	std::string getType() const override;

	bool useAbility();

	int nextMove;
};

