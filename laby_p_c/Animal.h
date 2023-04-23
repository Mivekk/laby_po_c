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
	virtual void draw() = 0;

	virtual bool bounceAttack(Organism* organism) override;
	virtual bool escaped() override;

	virtual std::string getType() const = 0;

	void move(std::pair<int, int> dest);
private:

	void breed(Animal* animal);
	void fight(Organism* organism);

	bool skipMove;
	bool didMove;
};

