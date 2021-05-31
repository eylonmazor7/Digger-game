#pragma once
#include "StaticObjects.h"

class Wall : public StaticObjects
{
public:
	using StaticObjects::StaticObjects; //using StaticObjects constructor
	~Wall() = default;

	virtual void collission(Objects& other) override;
	virtual void collission(Digger& other) override;
	virtual void collission(SmartMonster& other) override;
	virtual void collission(StupidMonster& other) override;
	
	virtual void collission(Wall& other) override {}
	virtual void collission(Diamond& other) override {}
	virtual void collission(ScoreGift& other) override {}
	virtual void collission(TimeGift& other) override {}
	virtual void collission(LifeGift& other) override {}
	virtual void collission(Rock& other) override {}
};