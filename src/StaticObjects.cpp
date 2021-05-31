#include "StaticObjects.h"

void StaticObjects::setExist(bool a) //set existance
{
	m_exist = a;
}

bool StaticObjects::getExist() const //is object exist right now
{
	return m_exist;
}

