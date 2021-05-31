#include "Menu.h"
#include <Windows.h> //for sleep()

Menu::Menu()
{
	createMenu();
}

void Menu::createMenu() //load pictures for all program
{
	m_startGame.loadFromFile("start.png");
	m_startGame.setSmooth(true);
	m_startIcon.setTexture(&m_startGame);
	m_startIcon.setOutlineColor(sf::Color::White);
	m_startIcon.setOutlineThickness(4);
		
	m_quit.loadFromFile("quit.png");
	m_quit.setSmooth(true);
	m_quitIcon.setTexture(&m_quit);
	m_quitIcon.setOutlineColor(sf::Color::White);
	m_quitIcon.setOutlineThickness(4);

	m_pic.loadFromFile("bg4.png");
	m_pic.setSmooth(true);
	m_picIcon.setTexture(&m_pic);

	m_logo.loadFromFile("pic.png");
	m_logo.setSmooth(true);
	m_logoPic.setTexture(&m_logo);

	m_font.loadFromFile("pokefont2.ttf");
	text.setFont(m_font);
	text.setCharacterSize(25);
	text.setLetterSpacing(2);
	text.setPosition(40.f, 850.f);
	text.setFillColor(sf::Color::Black);
	text.setString("Eylon Mazor & Dor Rozin");

	m_lose.loadFromFile("cry.png");
	m_lose.setSmooth(true);
	m_losePic.setTexture(&m_lose);

	m_win.loadFromFile("win.png");
	m_win.setSmooth(true);
	m_winPic.setTexture(&m_win);

	m_rocks.loadFromFile("rocks2.png");
	m_rocks.setSmooth(true);
	m_rocksPic.setTexture(&m_rocks);
}

void Menu::drawOptions(sf::RenderWindow& window) //draw open screen options
{
	m_startIcon.setSize(sf::Vector2f(200, 80));
	m_startIcon.setPosition(200.f, 470.f);
	window.draw(m_startIcon);

	m_quitIcon.setSize(sf::Vector2f(200, 80));
	m_quitIcon.setPosition(200.f, 590.f);
	window.draw(m_quitIcon);

	window.draw(text);
}

void Menu::drawPic(sf::RenderWindow& window) //draw open screen bg pic
{
	m_picIcon.setSize(sf::Vector2f(1200, 900));
	window.draw(m_picIcon);

	m_logoPic.setSize(sf::Vector2f(450, 300));
	m_logoPic.setPosition(65.f, 100.f);
	window.draw(m_logoPic);
}

sf::RectangleShape& Menu::getStartIcon()
{
	return m_startIcon;
}

void Menu::setStartIconBound(sf::Color color) //mouse on- change color
{
	m_startIcon.setOutlineColor(color);
}

sf::RectangleShape& Menu::getQuitIcon()
{
	return m_quitIcon;
}

void Menu::setQuitIconBound(sf::Color color) //mouse on- change color
{
	m_quitIcon.setOutlineColor(color);
}

void Menu::drawWinPic(sf::RenderWindow& window) //win game pic and options
{
	m_winPic.setSize(sf::Vector2f(1200, 900));
	window.draw(m_winPic);

	m_startIcon.setSize(sf::Vector2f(200, 80));
	m_startIcon.setPosition(900.f, 600.f);
	window.draw(m_startIcon);

	m_quitIcon.setSize(sf::Vector2f(200, 80));
	m_quitIcon.setPosition(900.f, 700.f);
	window.draw(m_quitIcon);
}

void Menu::drawLosePic(sf::RenderWindow& window)//lose game pic and options
{
	m_losePic.setSize(sf::Vector2f(1200, 900));
	window.draw(m_losePic);

	m_startIcon.setSize(sf::Vector2f(200, 80));
	m_startIcon.setPosition(150.f, 250.f);
	window.draw(m_startIcon);

	m_quitIcon.setSize(sf::Vector2f(200, 80));
	m_quitIcon.setPosition(150.f, 350.f);
	window.draw(m_quitIcon);
}

void Menu::drawRocksPic(sf::RenderWindow& window) //too much rocks pic
{
	sf::Font font1;
	font1.loadFromFile("pokefont2.ttf");
	sf::Text text;
	text.setFont(font1);

	text.setFillColor(sf::Color::Magenta);

	text.setCharacterSize(35);

	text.setLetterSpacing(2);

	text.setPosition(200.f, 650.f);

	text.setString("Can't Handle Too Many Rocks!");

	m_rocksPic.setSize(sf::Vector2f(1200, 920));

	window.clear();
	window.draw(m_rocksPic);
	window.draw(text);
	window.display();

	Sleep(800);
}