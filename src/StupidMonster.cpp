#include "StupidMonster.h"
#include "Digger.h"
#include "Controller.h"

sf::Vector2f& StupidMonster::setDirection() //set monster advancing direction
{
	float dt = Controller::getDt(); //to make it move by clock timing
	srand(time(NULL));
	int randNum = rand() % 4;

	sf::Vector2f direction(0.0f, 0.0f);

	switch (randNum)
	{
	case 0: direction.x = 35 * dt; break;
	case 1: direction.x = -35 * dt; break;
	case 2: direction.y = 35 * dt; break;
	case 3: direction.y = -35 * dt; break;
	}

	return direction;
}

void StupidMonster::collission(Objects& other) //stupid monster <---> object 
{
	other.collission(*this);
}

void StupidMonster::collission(Digger& other) //stupid monster <---> digger
{
	other.setLife(-1);
	Controller::setBool();
}

void StupidMonster::collission(Rock& other) //stupid monster <---> rock
{
	this->setWrongMoveBool(true);
}

void StupidMonster::collission(Wall& other) //stupid monster <---> wall
{
	this->setWrongMoveBool(true);
}