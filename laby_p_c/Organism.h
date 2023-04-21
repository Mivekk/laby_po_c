#pragma once
#include "World.h"

class Organism
{
public:
	Organism(World* world);
	virtual ~Organism();

	virtual void update() = 0;
	virtual void draw() = 0;

	int getStrength() const;
	int getInitiative() const;
	int getAge() const;
	std::pair<int, int> getPos() const;
protected:
	Console console;

	World* world;
	
	int strength;
	int initiative;
	int age;
	std::pair<int, int> pos;
	 
	virtual void handleCollision(Organism* other) = 0;
};

