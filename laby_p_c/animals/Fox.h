#pragma once
#include "../Animal.h"

class Fox : public Animal
{
public:
	Fox(World* world, std::pair<int, int> pos);
	~Fox();

private:
	std::pair<int, int> getNextPos() override;
	void draw() override;

	std::string getType() const override;
};

