#include "MobileObjects.h"
#include "Board.h"
#include "Digger.h"
#include "Controller.h"

MobileObjects::MobileObjects(sf::Vector2f pos, char c, sf::Texture tex) : Objects(pos, c)
{
	m_tex = tex;
	m_currPos = Objects::getStartPos();
	m_rec.setPosition(pos.x, pos.y);
	m_rec.setOutlineColor(sf::Color::Transparent);
	m_rec.setTexture(&m_tex);
}

sf::Vector2f& MobileObjects::getCurrPos()
{
	return m_currPos;
}

void MobileObjects::setCurrPos(sf::Vector2f& pos)
{
	m_currPos = pos;
}

void MobileObjects::setTex(sf::Texture tex)
{
	m_tex = tex;
	m_rec.setTexture(&m_tex);
}

void MobileObjects::setRec(sf::Vector2f pos) //set rectangle position
{
	m_rec.setPosition(pos.x, pos.y);
}

sf::RectangleShape& MobileObjects::getRec()
{
	return m_rec;
}

void MobileObjects::moveObjects()
{
	m_direction = setDirection();

	if (inBounds(m_direction))
		MoveObjectsByDirection();
}

bool MobileObjects::inBounds(sf::Vector2f& direction) //is next step in bounds
{
	if (this->getRec().getGlobalBounds().top + direction.y < 0 ||
		this->getRec().getGlobalBounds().left + direction.x < 0 ||
		this->getRec().getPosition().y + 70 + direction.y > 700 ||
		this->getRec().getPosition().x + 70 + direction.x > 1200)
		return false;

	return true;
}

void MobileObjects::MoveObjectsByDirection() //move mobile objects
{
	this->getRec().move(m_direction);
	sf::Vector2f temp = this->getRec().getPosition();
	this->setCurrPos(temp);

	if (this->getChar() == '/') //if its Digger
		Digger::setStaticDigPos(temp);
}

void MobileObjects::itsWrongMove() //make move not possible
{
	this->setWrongMoveBool(false);
	sf::Vector2f temp(this->getCurrPos());

	if (m_direction.x == 0) //the last move is or up or down
	{
		if (m_direction.y > 0)
			temp.y -= 5;
		else
			temp.y += 5;
	}
	else //the last move is or right or left
	{
		if (m_direction.x > 0)
			temp.x -= 5;
		else
			temp.x += 5;
	}

	this->getRec().setPosition(temp);
	this->setCurrPos(temp);

	if (this->getChar() == '/') //if its Digger
		Digger::setStaticDigPos(temp);
}

sf::Vector2f& MobileObjects::getDirection()
{
	return m_direction;
}

void MobileObjects::setWrongMoveBool(bool temp)
{
	m_wrongMove = temp;
}

bool MobileObjects::getBool() const
{
	return m_wrongMove;
}

void MobileObjects::setRecSize(sf::Vector2f size)
{
	m_rec.setSize(sf::Vector2f(size.x, size.y));
}