#pragma once
#include "StaticObjects.h"

class Gift : public StaticObjects
{
public:
	using StaticObjects::StaticObjects; //using static objects constructor
	~Gift () = default;

	virtual void collission(Objects&) = 0;
	virtual void collission(Digger& other) = 0;
	virtual void collission(SmartMonster&) = 0;
	virtual void collission(StupidMonster&) = 0;
	virtual void collission(Diamond&) = 0;
	virtual void collission(Rock&) = 0;
	virtual void collission(Wall&) = 0;
	virtual void collission(TimeGift&) = 0;
	virtual void collission(ScoreGift&) = 0;
	virtual void collission(LifeGift&) = 0;
	
};