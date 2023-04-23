#pragma once
#include "../Animal.h"

class Wolf : public Animal
{
public:
	Wolf(World* world, std::pair<int, int> pos);
	~Wolf();

private:
	void draw() override;

	std::string getType() const override;
};

