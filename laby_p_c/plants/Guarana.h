#pragma once
#include "../Plant.h"

#define STRENGTH_INCREMENT 3

class Guarana : public Plant
{
public:
	Guarana(World* world, std::pair<int, int> pos);
	~Guarana();

private:
	void handleCollision(Organism* other) override;
	void draw() override;

	std::string getType() const override;
};

