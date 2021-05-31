#pragma once
#include "Objects.h"
#include <SFML/Graphics.hpp>

class MobileObjects : public Objects
{
public:
	MobileObjects() {}
	~MobileObjects() = default;
	MobileObjects(sf::Vector2f, char, sf::Texture); //constructor

	sf::Vector2f& getCurrPos();
	sf::RectangleShape& getRec();
	void setRec(sf::Vector2f);
	void setCurrPos(sf::Vector2f&);
	void setTex(sf::Texture);
	void setRecSize(sf::Vector2f);

	sf::Vector2f& getDirection();
	bool getBool() const;
	void moveObjects();
	void itsWrongMove();
	void setWrongMoveBool(bool);
	void MoveObjectsByDirection();
	virtual sf::Vector2f& setDirection() = 0;
	virtual bool inBounds(sf::Vector2f&);

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
	bool m_wrongMove = false;

	sf::Texture m_tex;
	sf::Vector2f m_currPos;
	sf::RectangleShape m_rec;
	sf::Vector2f m_direction;
};