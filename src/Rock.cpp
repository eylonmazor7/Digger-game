#include "Rock.h"
#include "Digger.h"
#include "StupidMonster.h"

void Rock::collission(Objects& other)
{
	other.collission(*this);
}

void Rock::collission(Digger& other) //rock <---> digger 
{
	other.setRocks(-1);
	this->setExist(false);
}

void Rock::collission(StupidMonster& other) //rock <---> stupid monster
{
	other.setWrongMoveBool(true);
}