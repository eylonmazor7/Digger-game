#include "Toolbar.h"

Toolbar::Toolbar() //constructor- loading pics and font
{
	texture.loadFromFile("toolbar1.png");
	texture.setSmooth(true);
	picRec.setTexture(&texture);
	picRec.setSize(sf::Vector2f(1200, 200));
	picRec.setPosition(0, 700);
	font.loadFromFile("pokefont2.ttf");
	details.resize(5);
	for (int i = 0; i < 5; i++)
	{
		details[i].setFont(font);
		details[i].setCharacterSize(30);
		details[i].setFillColor(sf::Color::Blue);
	}
	details[0].setPosition(180, 830);
	details[1].setPosition(375, 830);
	details[2].setPosition(580, 830);
	details[3].setPosition(780, 830);
	details[4].setPosition(977, 830);

	bg.loadFromFile("blue.jpg");
	bg.setSmooth(true);
	bgPic.setTexture(&bg);
	bgPic.setSize(sf::Vector2f(1200, 200));
	bgPic.setPosition(0, 700);
}

void Toolbar::drawToolbarText(sf::RenderWindow& window, int level, int score, int life, int rocks, int time)
{
	//draw all text data visable during game
	for (int i = 0; i < 5; i++)
	{
		switch(i)
		{
			case 0:
				details[i].setString(convertIntToString(level));
				break;
				
			case 1:
				details[i].setString(convertIntToString(score));
				if (score < 10)
					details[i].setPosition(375, 830);
				else
					details[i].setPosition(367, 830);
				break;
				
			case 2:
				details[i].setString(convertIntToString(life));
				break;
				
			case 3:
				details[i].setString(convertIntToString(rocks));
				break;
				
			case 4:
				details[i].setString(convertIntToString(time));
				if (time >= 0 && time < 10)
					details[i].setPosition(985, 830);
				break;
		}
	}
	for (int i = 0; i < 5; i++)
		window.draw(details[i]);
}


std::string Toolbar::convertIntToString(int i) //convert int to text 
{
	std::stringstream itos;
	itos << i;
	return itos.str();
}

void Toolbar::drawToolbarPic(sf::RenderWindow& window)
{
	//window.draw(bgPic);
	window.draw(picRec);
}