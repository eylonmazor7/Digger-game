#include "Diamond.h"
#include "Digger.h"

int Diamond::m_count = 0;
int Diamond::backupCount = 0;

Diamond::Diamond(sf::Vector2f pos, char c) : StaticObjects(pos, c)
{
	m_count++;
	backupCount++;
}

int Diamond::getDiamondsCount()
{
	return m_count;
}


void Diamond::decCount() //decrease diamonds count by 1
{
	m_count--;
}

void Diamond::collission(Objects& other)
{
	other.collission(*this);
}

void Diamond::collission(Digger& other)
{
	m_count--;
	this->setExist(false);
	other.setScore(15);
}

void Diamond::resetCount() //recieve back number of starting count diamonds
{
	m_count = backupCount;
}

void Diamond::setToZero() //set diamond count to 0
{
	m_count = 0;
}