#include "Digger.h"
#include "Diamond.h"
#include "TimeGift.h"
#include "ScoreGift.h"
#include "LifeGift.h"
#include "Rock.h"
#include "SmartMonster.h"
#include "StupidMonster.h"
#include "Controller.h"

sf::Vector2f Digger::m_myPos;

sf::Vector2f& Digger::setDirection() //set digger advance direction
{
	float dt = Controller::getDt();
	sf::Vector2f vec(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		vec.y = dt * (-150);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		vec.y = dt * (150);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		vec.x = dt * (150);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		vec.x = dt * (-150);
	return vec;
}

void Digger::collission(Objects& other)
{
	other.collission(*this);
}

void Digger::collission(SmartMonster& other)
{
	m_life--;
	Controller::setBool();
}

void Digger::collission(StupidMonster& other)
{
	m_life--;
	Controller::setBool();
}

void Digger::collission(Diamond& other)
{
	other.decCount();
	other.setExist(false);
	m_score += 15;
}

void Digger::collission(Rock& other)
{
	m_rocksAllowed--;
	other.setExist(false);
}

void Digger::collission(Wall& other)
{
	this->setWrongMoveBool(true);
}

void Digger::collission(TimeGift& other)
{
	m_time +=10;
	other.setExist(false);
}

void Digger::collission(ScoreGift& other)
{
	m_score += 15;
	other.setExist(false);
}

void Digger::collission(LifeGift& other)
{
	m_time += 10;
	other.setExist(false);
}

int Digger::getScore() const
{
	return m_score;
}

void Digger::setScore(int score)
{
	m_score += score;
}

int Digger::getLevel() const
{
	return m_level;
}

void Digger::setLevel(int level)
{
	m_level += level;
}

int Digger::getLife() const
{
	return m_life;
}

void Digger::setStartLife()
{
	m_life = 3;
}

int Digger::getRocks() const
{
	return m_rocksAllowed;
}

void Digger::setRocks(int rocks)
{
	m_rocksAllowed += rocks;
}

void Digger::setStartRocks()
{
	m_rocksAllowed = 0;
}

int Digger::getTime() const
{
	return m_time;
}

void Digger::setTime(int time)
{
	m_time += time;
}

void Digger::setTimeStart()
{
	m_time = 0;
}

void Digger::setlevelStart()
{
	m_level = 0;
}

void Digger::setStartScore()
{
	m_score = 0;
}

void Digger::setLife(int a)
{
	m_life += a;
}

sf::Vector2f Digger::digPos()
{
	return m_myPos;
}

void Digger::setStaticDigPos(sf::Vector2f& a)
{
	m_myPos.x = a.x;
	m_myPos.y = a.y;
}
