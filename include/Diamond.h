#pragma once
#include "StaticObjects.h"
#include <SFML/Graphics.hpp>

class Diamond : public StaticObjects
{
public:
	Diamond(sf::Vector2f,char); //constuctor
	~Diamond () = default;

	void decCount();
	static void resetCount();
	static void setToZero();
	static int getDiamondsCount();

	virtual void collission(Objects& other) override;
	virtual void collission(Digger& other) override;

	virtual void collission(SmartMonster& other) override {}
	virtual void collission(StupidMonster& other) override {}
	virtual void collission(Diamond& other) override {}
	virtual void collission(Wall& other) override {}
	virtual void collission(LifeGift& other) override {}
	virtual void collission(ScoreGift& other) override {}
	virtual void collission(TimeGift& other) override {}
	virtual void collission(Rock& other) override {}
	
private:

	static int m_count;
	static int backupCount;
};