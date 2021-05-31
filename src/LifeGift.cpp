#include "LifeGift.h"
#include "Digger.h"

void LifeGift::collission(Objects& other)
{
	other.collission(*this);
}

void LifeGift::collission(Digger& other) //life gift <---> digger
{
	other.setLife(1);
	this->setExist(false);
}