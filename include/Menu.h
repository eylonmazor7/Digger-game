#pragma once
#include <SFML/Graphics.hpp>


class Menu
{
public:
	Menu(); //constructor
	~Menu() = default;
	void createMenu();
	void drawOptions(sf::RenderWindow&);
	void drawPic(sf::RenderWindow&);
	sf::RectangleShape& getStartIcon();
	void setStartIconBound(sf::Color);
	sf::RectangleShape& getQuitIcon();
	void setQuitIconBound(sf::Color);

	void drawWinPic(sf::RenderWindow&);
	void drawLosePic(sf::RenderWindow&);
	void drawRocksPic(sf::RenderWindow&);

private:
	sf::Texture m_startGame;
	sf::Texture m_quit;
	sf::Texture m_pic;
	sf::Texture m_logo;
	sf::RectangleShape m_startIcon;
	sf::RectangleShape m_quitIcon;
	sf::RectangleShape m_picIcon;
	sf::RectangleShape m_logoPic;

	sf::Font m_font;
	sf::Text text;

	sf::Texture m_win;
	sf::Texture m_lose;
	sf::Texture m_rocks;

	sf::RectangleShape m_winPic;
	sf::RectangleShape m_losePic;
	sf::RectangleShape m_rocksPic;


};