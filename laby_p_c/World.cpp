#include <fstream>
#include "World.h"
#include "animals/Wolf.h"
#include "animals/Sheep.h"
#include "animals/Human.h"
#include "animals/Fox.h"
#include "animals/Turtle.h"
#include "animals/Antelope.h"
#include "plants/Grass.h"
#include "plants/Dandelion.h"
#include "plants/Guarana.h"
#include "plants/Belladonna.h"
#include "plants/Sosnowsky.h"

#define ARROW 224

World::World(std::pair<int, int> size)
	: console(new Console()), human(nullptr), worldSize(size), organismsSize(0)
{
	// adjust board size
	board.resize(worldSize.second, std::vector<Organism*>(worldSize.first, nullptr));

	init();
}

World::~World()
{
}

void World::addOrganism(Organism* organism)
{
	organisms.push_back(organism);

	organismsSize++;
}

void World::removeOrganism(Organism* organism)
{
	auto it = std::find(organisms.begin(), organisms.end(), organism);
	int organismIdx = it - organisms.begin();
	if (organismIdx >= 0) {
		if (typeid(*organisms[organismIdx]) == typeid(Human)) {
			delete human;
			human = nullptr;
		}
		else {
			delete organisms[organismIdx];
		}
		organisms[organismIdx] = nullptr;

		organisms.erase(it);

		organismsSize--;
	}
}

void World::init()
{
	std::pair<int, int> randomPos = { rand() % worldSize.first, rand() % worldSize.second };

	randomPosition(randomPos);
	organisms.push_back(new Wolf(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Wolf(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Sheep(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Sheep(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Fox(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Fox(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Turtle(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Turtle(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Antelope(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Antelope(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Grass(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Guarana(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Belladonna(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Sosnowsky(this, randomPos));

	randomPosition(randomPos);
	organisms.push_back(new Dandelion(this, randomPos));

	randomPosition(randomPos);
	human = new Human(this, randomPos);
	organisms.push_back(human);

	console->textColor(WHITE);
	console->backgroundColor(BLACK);
	system("cls");
	
	run();
}

void World::run()
{
	draw();
	while (true) {
		readInput();

		update();

		draw();
	}
}

void World::readInput()
{
	int input = _getch();
	if (input == ARROW) {
		input = _getch();
		if (human != nullptr) {
			human->setNextMove(input);
		}
	}
	else if ((char)input == 'p' && human != nullptr && !human->abilityActivated && human->abilityCooldown < 0) {
		human->abilityActivated = true;
		human->abilityDuration = ABILITY_DURATION;
	}
	else if ((char)input == 's') {
		save();
	}
	else if ((char)input == 'l') {
		load();
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

	if (human != nullptr) {
		if (human->abilityDuration == -1 && human->abilityActivated) {
			human->abilityActivated = false;
			human->abilityCooldown = ABILITY_COOLDOWN;
		}
		else {
			human->abilityDuration--;
			human->abilityCooldown--;
		}
	}

	console->setup(25, 28);
	std::cout << organismsSize;

	console->displayLogs();
}

void World::draw()
{
	int startY = 1;
	console->gotoxy(2, startY);
	console->textColor(WHITE);

	for (int i = 0; i < worldSize.second; i++) {
		for (int j = 0; j < worldSize.first; j++) {
			if (board[i][j] == nullptr) {
				console->backgroundColor(WHITE);

				std::cout << "*";
			}
			else {
				board[i][j]->draw();
			}
			std::cout << " ";
		}
		console->gotoxy(2, startY + i + 1);
	}
}

void World::save()
{
	std::ofstream file("save.txt");

	file << organisms.size() << " " << organismsSize << "\n";

	for (int i = 0; i < organisms.size(); i++) {
		file << organisms[i]->getStrength() << " " << organisms[i]->getAge() << 
			" " << organisms[i]->getPos().first << " " << organisms[i]->getPos().second << 
			" " << organisms[i]->getType() << " ";

		if (organisms[i]->getType() == "Human") {
			file << human->abilityActivated << " " << human->abilityCooldown << " " << human->abilityDuration;
		}

		file << "\n";
	}

	file.close();
}

void World::load()
{
	std::ifstream file("save.txt");

	organisms.clear();
	board.clear();

	int oSize;
	file >> oSize >> organismsSize;

	std::vector<Organism*> newOrganisms;

	std::vector<std::vector<Organism*>> newBoard(worldSize.second, std::vector<Organism*>(worldSize.first, nullptr));
	board = newBoard;

	for (int i = 0; i < oSize; i++) {
		int tmpStrength, tmpAge;
		std::pair<int, int> tmpPos;
		std::string tmpType;

		file >> tmpStrength >> tmpAge >> tmpPos.first >> tmpPos.second >> tmpType;

		if (tmpType == "Antelope") {
			newOrganisms.push_back(new Antelope(this, tmpPos));
		} 
		else if (tmpType == "Fox") {
			newOrganisms.push_back(new Fox(this, tmpPos));
		}
		else if (tmpType == "Sheep") {
			newOrganisms.push_back(new Sheep(this, tmpPos));
		}
		else if (tmpType == "Turtle") {
			newOrganisms.push_back(new Turtle(this, tmpPos));
		}
		else if (tmpType == "Human") {
			human = new Human(this, tmpPos);
			newOrganisms.push_back(human);
			file >> human->abilityActivated >> human->abilityCooldown >> human->abilityDuration;
		}
		else if (tmpType == "Wolf") {
			newOrganisms.push_back(new Wolf(this, tmpPos));
		}
		else if (tmpType == "Belladonna") {
			newOrganisms.push_back(new Belladonna(this, tmpPos));
		}
		else if (tmpType == "Dandelion") {
			newOrganisms.push_back(new Dandelion(this, tmpPos));
		}
		else if (tmpType == "Grass") {
			newOrganisms.push_back(new Grass(this, tmpPos));
		}
		else if (tmpType == "Guarana") {
			newOrganisms.push_back(new Guarana(this, tmpPos));
		}
		else if (tmpType == "Sosnowsky") {
			newOrganisms.push_back(new Sosnowsky(this, tmpPos));
		}
		newOrganisms.back()->setStrength(tmpStrength);
		newOrganisms.back()->setAge(tmpAge);
	}

	organisms = newOrganisms;

	file.close();
}

void World::randomPosition(std::pair<int, int>& randomPos)
{
	while (board[randomPos.second][randomPos.first] != nullptr) {
		randomPos = { rand() % worldSize.first, rand() % worldSize.second };
	}
}
