#pragma once
#include "../Animal.h"

#define ESCAPE_CHANCE 50

class Antelope : public Animal
{
public:
	Antelope(World* world, std::pair<int, int> pos);
	~Antelope();

private:
	std::pair<int, int> getNextPos() override;
	void draw() override;
	bool escaped() override;

	std::string getType() const override;
};

