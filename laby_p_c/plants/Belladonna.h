#pragma once
#include "../Plant.h"

class Belladonna : public Plant
{
public:
	Belladonna(World* world, std::pair<int, int> pos);
	~Belladonna();

private:
	void handleCollision(Organism* other) override;
	void draw() override;

	std::string getType() const override;
};

