#pragma once
#include "../Plant.h"

class Sosnowsky : public Plant
{
public:
	Sosnowsky(World* world, std::pair<int, int> pos);
	~Sosnowsky();

private:
	void update() override;
	void handleCollision(Organism* other) override;
	void draw() override;

	std::string getType() const override;
};

