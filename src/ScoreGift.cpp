#include "ScoreGift.h"
#include "Digger.h"

void ScoreGift::collission(Objects& other)
{
	other.collission(*this);
}

void ScoreGift::collission(Digger& other) //score gift <---> digger
{
	other.setScore(15);
	this->setExist(false);
}
