#pragma once
#include <SFML/Graphics.hpp>

//forward declaration of all objects in project
class MobileObjects;
class Digger;
class Monster;
class StupidMonster;
class SmartMonster;
class StaticObjects;
class Gift;
class Diamond;
class Rock;
class Wall;
class ScoreGift;
class TimeGift;
class LifeGift;

class Objects
{
public:
	Objects() {}
	Objects(sf::Vector2f, char); //constructor
	~Objects() = default;

	sf::Vector2f& getStartPos();
	void setStartPos(sf::Vector2f&);
	char getChar() const;
	void setChar(char);

	virtual void collission(Objects&) = 0;
	virtual void collission(Digger&) = 0;
	virtual void collission(SmartMonster&) = 0;
	virtual void collission(StupidMonster&) = 0;
	virtual void collission(Diamond&) = 0;
	virtual void collission(Rock&) = 0;
	virtual void collission(Wall&) = 0;
	virtual void collission(TimeGift&) = 0;
	virtual void collission(ScoreGift&) = 0;
	virtual void collission(LifeGift&) = 0;

private:
	sf::Vector2f m_startPos;
	char m_char;
};