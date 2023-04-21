#include "World.h"
#include "animals/Wolf.h"
#include "animals/Sheep.h"

World::World(std::pair<int, int> size)
	: worldSize(size), organismsSize(0)
{
	// adjust board size
	board.resize(worldSize.second, std::vector<Organism*>(worldSize.first, nullptr));

	init();
}

World::~World()
{
}

void World::removeOrganism(Organism* organism)
{
	auto it = std::find(organisms.begin(), organisms.end(), organism);
	int organismIdx = it - organisms.begin();
	if (organismIdx >= 0 && organismIdx < organismsSize) {
		try {
			delete organisms[organismIdx];
			organisms[organismIdx] = nullptr;
			organisms.erase(it);

			organismsSize--;
		}
		catch (const std::string& exception) {
			console.write(25, 20);
			std::cout << exception << "\n";
		}
	}
}

void World::init()
{
	organisms.push_back(new Wolf(this, { 1, 1 }));
	organisms.push_back(new Wolf(this, { 2, 2 }));
	organisms.push_back(new Sheep(this, { 18, 18 }));
	organisms.push_back(new Sheep(this, { 17, 17 }));

	console.textColor(WHITE);
	console.backgroundColor(BLACK);
	system("cls");
	
	run();
}

void World::run()
{
	draw();
	while (true) {
		int input = _getch();

		update();
		draw();
	}
}

void World::update()
{
	std::sort(organisms.begin(), organisms.end(), 
		[](const Organism* a, const Organism* b) 
	{
		if (a->getInitiative() == b->getInitiative()) {
			return a->getAge() > b->getAge();
		}

		return a->getInitiative() > b->getInitiative();
	});

	organismsSize = organisms.size();

	for (int i = 0; i < organismsSize; i++) {
		organisms[i]->update();
	}
}

void World::draw()
{
	console.gotoxy(0, 0);
	console.textColor(WHITE);

	for (int i = 0; i < worldSize.second; i++) {
		for (int j = 0; j < worldSize.first; j++) {
			if (board[i][j] == nullptr) {
				console.backgroundColor(WHITE);

				std::cout << "*";
			}
			else {
				board[i][j]->draw();
			}
			std::cout << " ";
		}
		std::cout << "\n";
	}
}
