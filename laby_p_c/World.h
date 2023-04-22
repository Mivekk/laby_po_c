#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <algorithm>

#include "Console.h"

class Organism;

class World
{
public:
	World(std::pair<int, int> size);
	~World();

	std::vector<Organism*> organisms;
	std::vector<std::vector<Organism*>> board;

	void addOrganism(Organism* organism);
	void removeOrganism(Organism* organism);
	void replaceOrganism(Organism* from, Organism* to);
private:
	Console console;

	void init();
	void run();
	void update();
	void draw();

	std::pair<int, int> worldSize;
	std::size_t organismsSize;
};

