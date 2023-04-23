#pragma once
#include "Organism.h"

#define REGROW_CHANCE 30

class Plant : public Organism
{
public:
	Plant(World* world, std::pair<int, int> pos);
	virtual ~Plant();

protected:
	virtual void update() override;
	virtual void handleCollision(Organism* other) override;
	virtual void draw() = 0;

	virtual std::string getType() const = 0;

	bool didRegrow;
};

