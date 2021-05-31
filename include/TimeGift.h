#pragma once
#include "Gift.h"

class TimeGift : public Gift
{
public:
	using Gift::Gift;
	~TimeGift() = default;

	virtual void collission(Objects& other) override;
	virtual void collission(Digger& other) override;

	virtual void collission(SmartMonster& other) override {}
	virtual void collission(StupidMonster& other) override {}
	virtual void collission(Diamond& other) override {}
	virtual void collission(ScoreGift& other) override {}
	virtual void collission(TimeGift& other) override {}
	virtual void collission(LifeGift& other) override {}
	virtual void collission(Rock& other) override {}
	virtual void collission(Wall& other) override {}

private:


};