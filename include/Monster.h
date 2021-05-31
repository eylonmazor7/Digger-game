#pragma once
#include"MobileObjects.h"
#include <SFML/Graphics.hpp>
//#include "Controller.h"

class Monster : public MobileObjects
{
public:
	using MobileObjects::MobileObjects; //using mobile objects constructor
	~Monster() = default;

	sf::Vector2f& setDirection() = 0;

	virtual void collission(Objects& other) = 0;
	virtual void collission(Digger& other) = 0;
	virtual void collission(SmartMonster& other) = 0;
	virtual void collission(StupidMonster& other) = 0;
	virtual void collission(Diamond& other) = 0;
	virtual void collission(Rock& other) = 0;
	virtual void collission(Wall& other) = 0;
	virtual void collission(TimeGift& other) = 0;
	virtual void collission(ScoreGift& other) = 0;
	virtual void collission(LifeGift& other) = 0;

};