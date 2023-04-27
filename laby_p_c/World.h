#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <algorithm>

#include "Console.h"

#define ABILITY_COOLDOWN 5
#define ABILITY_DURATION 5

#define MIN_ORGANISMS 2
#define MAX_ORGANISMS 4

class Organism;
class Human;

class World
{
public:
	World(std::pair<int, int> size);
	~World();

	Console* console;

	std::vector<Organism*> organisms;
	std::vector<std::vector<Organism*>> board;

	void addOrganism(Organism* organism);
	void removeOrganism(Organism* organism);
private:
	Human* human;

	void init();
	void run();

	bool readInput();
	void update();

	void draw();
	void drawLegend();
	void drawOrganismLegend(int color, const std::string& name);

	void save();
	void load();

	void generateOrganisms();
	void randomPosition(std::pair<int, int>& randomPos);

	std::pair<int, int> worldSize;
	std::size_t organismsSize;
};

