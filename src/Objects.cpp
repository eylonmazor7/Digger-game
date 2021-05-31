#include "Objects.h"

Objects::Objects(sf::Vector2f pos, char c = NULL) : m_char(c), m_startPos(pos) //replace the NULL!!!
{
}

sf::Vector2f& Objects::getStartPos()
{
	return m_startPos;
}

void Objects::setStartPos(sf::Vector2f& pos)
{
	m_startPos = pos;
}

char Objects::getChar() const
{
	return m_char;
}

void Objects::setChar(char a)
{
	m_char = a;
}
