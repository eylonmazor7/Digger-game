#pragma once
#include "Monster.h"
#include <SFML/Graphics.hpp>

class SmartMonster : public Monster
{
public:
	using Monster::Monster; //using monster constructor
	~SmartMonster() = default;

	virtual sf::Vector2f& setDirection() override;
	

	virtual void collission(Objects& other) override;
	virtual void collission(Digger& other) override;
	virtual void collission(Wall& other) override;

	virtual void collission(Diamond& other) {}
	virtual void collission(Rock& other) {}
	virtual void collission(StupidMonster& other) {}
	virtual void collission(SmartMonster& other) {}
	virtual void collission(TimeGift& other) {}
	virtual void collission(ScoreGift& other) {}
	virtual void collission(LifeGift& other) {}

private:
	
};