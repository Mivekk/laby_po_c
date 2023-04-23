#pragma once
#include "../Plant.h"

class Grass : public Plant
{
public:
	Grass(World* world, std::pair<int, int> pos);
	~Grass();

private:
	void draw() override;

	std::string getType() const override;
};

