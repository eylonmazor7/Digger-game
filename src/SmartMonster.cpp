#include "SmartMonster.h"
#include "Digger.h"
#include "Controller.h"

sf::Vector2f& SmartMonster::setDirection() //set smart monster direction according to digger direction
{
	float dt = Controller::getDt();
	sf::Vector2f DiggerPos(Digger::digPos());

	int witdh = this->getCurrPos().x - DiggerPos.x;
	int height = this->getCurrPos().y - DiggerPos.y;

	sf::Vector2f retPos(0.0f,0.0f);

	if (!height)
		witdh > 0 ? retPos.x = -50*dt : retPos.x = 50*dt;

	else if (!witdh)
		height > 0 ? retPos.y = -50*dt : retPos.y = 50*dt;
		
	else if (height > 0 && witdh > 0)
		height >= witdh ? retPos.y = -50*dt : retPos.x = -50*dt;
	
	else if (height < 0 && witdh > 0)
		abs(height) >= witdh ? retPos.y = 50*dt : retPos.x = -50*dt;
									
	else if (height > 0 && witdh < 0)
		height >= abs(witdh) ? retPos.y = -50*dt : retPos.x = 50*dt;
								
	else if (height < 0 && witdh < 0)
		abs(height) >= abs(witdh) ? retPos.y = 50*dt : retPos.x = 50*dt;
											
	return retPos;
}

void SmartMonster::collission(Objects& other) //smart monster <---> object
{
	other.collission(*this);
}

void SmartMonster::collission(Digger& other) //smart monster <---> digger
{
	other.setLife(-1);
	Controller::setBool();
}

void SmartMonster::collission(Wall& other) //smart monster <---> wall
{
	this->setWrongMoveBool(true);
}