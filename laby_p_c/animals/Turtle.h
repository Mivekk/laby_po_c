#pragma once
#include "../Animal.h"

#define MOVE_CHANCE 25

class Turtle : public Animal
{
public:
	Turtle(World* world, std::pair<int, int> pos);
	~Turtle();

private:
	std::pair<int, int> getNextPos() override;
	void draw() override;
	bool bounceAttack(Organism* organism) override;

	std::string getType() const override;
};

