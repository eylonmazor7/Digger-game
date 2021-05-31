#include "TimeGift.h"
#include "Digger.h"

void TimeGift::collission(Objects& other) //time gift <---> object
{
	other.collission(*this);
}

void TimeGift::collission(Digger& other) //time gift <---> digger
{
	other.setTime(10);
	this->setExist(false);
}

