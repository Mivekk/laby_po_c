#pragma once
#include "World.h"

class Organism
{
public:
	Organism(World* world);
	virtual ~Organism();

	virtual void update() = 0;
	virtual void handleCollision(Organism* other) = 0;
	virtual void draw() = 0;

	virtual bool bounceAttack(Organism* organism) { return false; };
	virtual bool escaped() { return false; };

	virtual std::string getType() const = 0;

	virtual std::pair<int, int> getNextPos();

	void setStrength(int newStrength);
	void setInitiative(int newInitiative);
	void setAge(int newAge);
	void setPos(std::pair<int, int> newPos);

	int getStrength() const;
	int getInitiative() const;
	int getAge() const;
	std::pair<int, int> getPos() const;

	std::pair<int, int> findFreeSpace(std::pair<int, int> startPos);
protected:
	World* world;
	
	int strength;
	int initiative;
	int age;
	std::pair<int, int> pos;
};

