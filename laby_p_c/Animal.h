#pragma once
#include "Organism.h"

class Animal : public Organism
{
public:
	Animal(World* world, std::pair<int, int> pos);
	virtual ~Animal();

protected:
	virtual void update() override;
	virtual void handleCollision(Organism* other) override;
	virtual void draw() override;

	void breed(Animal* animal);
	void fight(Organism* organism);

private:
	bool skipMove;
	bool didMove;

	std::pair<int, int> findFreeSpace(std::pair<int, int> pos1, std::pair<int, int> pos2);
};

