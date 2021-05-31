#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

const int DETAILS = 5;
const int SIZE = 70;

class Toolbar
{
public:
	Toolbar(); //constructor
	~Toolbar() = default;

	void drawToolbarPic(sf::RenderWindow&);
	void drawToolbarText(sf::RenderWindow&, int, int, int, int, int);

	std::string convertIntToString(int i);

private:

	sf::RectangleShape picRec;
	sf::RectangleShape bgPic;
	sf::Texture texture;
	sf::Texture bg;
	sf::Font font;
	sf::Text text;
	std::vector <sf::Text> details;
};