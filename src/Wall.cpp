#include "Wall.h"
#include "Digger.h"
#include "Controller.h"

void Wall::collission(Objects& other) //wall <----> any object collision
{
	other.collission(*this);
}

void Wall::collission(Digger& other) //wall <---> digger collision
{
	other.setWrongMoveBool(true);
}

void Wall::collission(SmartMonster& other) //wall <---> smart monster 
{
	other.setWrongMoveBool(true);
}

void Wall::collission(StupidMonster& other) //wall <---> smart monster
{
	other.setWrongMoveBool(true);
}