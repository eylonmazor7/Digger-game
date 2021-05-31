#pragma once
#include "StaticObjects.h"

class Rock : public StaticObjects
{
public:
	using StaticObjects::StaticObjects; //using static object consturctor
	~Rock() = default;

	virtual void collission(Objects& other) override;
	virtual void collission(Digger& other) override;
	virtual void collission(StupidMonster& other) override;

	virtual void collission(SmartMonster& other) override {}
	virtual void collission(Diamond&) override {}
	virtual void collission(Rock&) override {}
	virtual void collission(Wall&) override {}
	virtual void collission(TimeGift&) override {}
	virtual void collission(ScoreGift&) override {}
	virtual void collission(LifeGift&) override {}
};