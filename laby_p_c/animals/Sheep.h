#pragma once
#include "../Animal.h"

class Sheep : public Animal
{
public:
	Sheep(World* world, std::pair<int, int> pos);
	~Sheep();

private:
	void draw() override;
};

