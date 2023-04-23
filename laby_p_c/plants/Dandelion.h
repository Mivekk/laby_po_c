#pragma once
#include "../Plant.h"

#define REGROW_TRIES 3

class Dandelion : public Plant
{
public:
	Dandelion(World* world, std::pair<int, int> pos);
	~Dandelion();

private:
	void update() override;
	void draw() override;

	std::string getType() const override;
};

