#include "Controller.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

bool Controller::DiggerMonsterCollision = false;
float Controller::dt = 0;

Controller::Controller() //load song, pic and font
{
	m_font.loadFromFile("pokefont2.ttf");
	m_tex.loadFromFile("bg9.png");
	m_tex.setSmooth(true);
	m_bgPic.setTexture(&m_tex);
	m_bgPic.setSize(sf::Vector2f(1200, 900));
	m_music.openFromFile("pokesong.ogg");
	m_music.play();
	m_music.setLoop(true);
}

void Controller::run() //run game
{
	sf::RenderWindow window(sf::VideoMode(1200.f, 900.f), "Play Digger", sf::Style::Close); //open window
	bool moveNextLevel, gameDone = false;

	startMenuFunc(window); //opening screen, before game

	if (!window.isOpen())
		return;

	m_board.loadTextures(); //set textures to all objects

	while (true)
	{
		moveNextLevel = false;
				
		if (!m_board.readBoard()) //check if there are more levels
		{
			if (endGameMenuWin(window)) //chose quit on end game menu- quit game
				return;

			else //read level again
				continue;
		}

		while (window.isOpen())
		{
			window.clear();

			window.draw(m_bgPic);
			drawBoard(window);
			//drawToolbar(window);
			m_board.getToolbar().drawToolbarPic(window); //toolbar picture
			m_board.getToolbar().drawToolbarText(window, m_board.getDigger().getLevel(),
				m_board.getDigger().getScore(), m_board.getDigger().getLife(),
				m_board.getDigger().getRocks(), m_board.getDigger().getTime()); //toolbar details

			window.display();

			dt = m_deltaTime.restart().asSeconds(); //for move
			
			if (m_board.getTime() > 0) //if the time is factor
				timeFunc();

			for (auto event = sf::Event{}; window.pollEvent(event);) {
				switch (event.type) {
					case sf::Event::Closed:
						window.close();
						m_board.cleanVectors();
						return;

					default:break;
				}
			}
			
			m_board.moveObjects(); //move all mobile objects
			m_board.checkCollisions(); //check collisions for every object
			m_board.checkIfWrongMove(); //check if move legal

			checkGame(window, moveNextLevel, gameDone); //check what condition the game is at
			
			if (gameDone) return; //game finished- no more playing
			
			if (moveNextLevel) 	break;	//move to next level	
		}
	}
}

void Controller::startMenuFunc(sf::RenderWindow& window) //starting screen menu
{
	bool isMenuOpen = true;
	while (window.isOpen())
	{
		window.clear();

		m_board.getMenu().drawPic(window);
		m_board.getMenu().drawOptions(window);

		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (isMouseOver(window, m_board.getMenu().getQuitIcon())) //quit game button pressed
					window.close();

				if (isMouseOver(window, m_board.getMenu().getStartIcon())) //start game button pressed
				{
					window.clear();
					isMenuOpen = false;
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved: //colorized buttons
				if (isMouseOver(window, m_board.getMenu().getStartIcon()))
					m_board.getMenu().setStartIconBound(sf::Color::Magenta);
				else
					m_board.getMenu().setStartIconBound(sf::Color::White);

				if (isMouseOver(window, m_board.getMenu().getQuitIcon()))
					m_board.getMenu().setQuitIconBound(sf::Color::Magenta);
				else
					m_board.getMenu().setQuitIconBound(sf::Color::White);
			}
		}
		if (!isMenuOpen)
			break;

		window.display();
	}
}

bool Controller::isMouseOver(sf::RenderWindow& window, sf::RectangleShape shape)
{
	sf::FloatRect shapePos = shape.getGlobalBounds();

	if (shapePos.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		return true;
	return false;
}


void Controller::drawBoard(sf::RenderWindow& window) //draw everything on the window							 
{
	m_board.drawDigger(window);
	m_board.drawMonsters(window);
	m_board.drawStatics(window);
}

void Controller::checkGame(sf::RenderWindow& window, bool& moveNextLevel, bool& gameDone) //check game conditions
{
	switch (checkGameRules())
	{
	case Options::RocksStackDone:
		restartLevelFunc();
		m_board.getMenu().drawRocksPic(window);
		m_board.getDigger().setRocks(m_board.getRocksAllowed());
		break;

	case Options::RestartMobile: //collision between digger and monsters
		m_board.restartMobilePos();

		if (m_board.getTime() > 0)
			m_board.getDigger().setTime(2);

		break;

	case Options::NextLevel:
		m_board.cleanVectors();
		m_board.getDigger().setScore(20);
		m_board.getDigger().setTimeStart();
		moveNextLevel = true;
		break;

	case Options::GameOver:
		if (endGameMenuLost(window))
			gameDone = true;
		else
			moveNextLevel = true;
		break;

	case Options::TimesUp:
		restartLevelFunc();
		break;

	case Options::Nothing: break;
	}
}

Options Controller::checkGameRules() //rules forcing
{
	if (m_board.getDigger().getTime() == 0)
		return Options::TimesUp;

	if (Diamond::getDiamondsCount() == 0) //end level
		return Options::NextLevel;
	
	if (m_board.getDigger().getRocks() == 0 && m_board.getDigger().getLife() > 0)
		return Options::RocksStackDone;

	if (m_board.getDigger().getLife() == 0) 
		return Options::GameOver;

	if (DiggerMonsterCollision)
	{
		DiggerMonsterCollision = false;
		return Options::RestartMobile;
	}
	return Options::Nothing;
}

void Controller::setBool()
{
	DiggerMonsterCollision = true;
}

float Controller::getDt()
{
	return dt;
}

void Controller::restartLevelFunc() //restart level
{
	m_board.getDigger().setLife(-1);
	m_board.restartStaticPos();
	m_board.restartMobilePos();
	Diamond::resetCount();
	
	if (m_board.getTime() > 0)
		m_board.getDigger().setTime(m_board.getTime());
}

bool Controller::endGameMenuWin(sf::RenderWindow& window) //end game menu screen
{
	m_board.cleanVectors();
	sf::Font font;
	font.loadFromFile("pokefont2.ttf");
	sf::Text text1, text2, text3, text4;
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text4.setFont(font);
	text1.setPosition(860.f, 100.f);
	text2.setPosition(750.f, 150.f);
	text3.setPosition(52.f, 600.f);
	text4.setPosition(200.f, 700.f);
	text1.setCharacterSize(45);
	text2.setCharacterSize(45);
	text3.setCharacterSize(60);
	text4.setCharacterSize(50);
	text1.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);
	text3.setFillColor(sf::Color::White);
	text4.setFillColor(sf::Color::White);
	text3.setLetterSpacing(2);
	text4.setLetterSpacing(2);
	text1.setString("You Win!");
	text2.setString("Wish To Play Again?");
	text3.setString("Your Score:");
	text4.setString(m_board.getToolbar().convertIntToString(m_board.getDigger().getScore()));

	while (window.isOpen())
	{
		window.clear();

		m_board.getMenu().drawWinPic(window);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);

		window.display();

		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (isMouseOver(window, m_board.getMenu().getQuitIcon()))
					window.close();

				if (isMouseOver(window, m_board.getMenu().getStartIcon()))
				{
					m_board.setFilePointer();
					m_board.getDigger().setlevelStart(); //make the level -> 1
					m_board.getDigger().setStartLife(); //make the life -> 3
					m_board.getDigger().setStartScore(); //make the score -> 0
					m_board.getDigger().setStartRocks();
					Diamond::setToZero();
					return false;
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				if (isMouseOver(window, m_board.getMenu().getStartIcon()))
					m_board.getMenu().setStartIconBound(sf::Color::Magenta);
				else
					m_board.getMenu().setStartIconBound(sf::Color::White);

				if (isMouseOver(window, m_board.getMenu().getQuitIcon()))
					m_board.getMenu().setQuitIconBound(sf::Color::Magenta);
				else
					m_board.getMenu().setQuitIconBound(sf::Color::White);
			}
		}
	}

	return true;
}

bool Controller::endGameMenuLost(sf::RenderWindow& window) //end game lost menu screen
{
	m_board.cleanVectors();

	sf::Text text1, text2;
	text1.setFont(m_font);
	text2.setFont(m_font);
	text1.setPosition(120.f, 100.f);
	text2.setPosition(10.f, 150.f);
	text1.setCharacterSize(45);
	text2.setCharacterSize(45);
	text1.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);

	text1.setString("You Lose!");
	text2.setString("Wish To Play Again?");

	while (window.isOpen())
	{
		window.clear();

		m_board.getMenu().drawLosePic(window);
		window.draw(text1);
		window.draw(text2);

		window.display();

		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (isMouseOver(window, m_board.getMenu().getQuitIcon()))
					window.close();

				if (isMouseOver(window, m_board.getMenu().getStartIcon()))
				{
					m_board.setFilePointer();
					m_board.getDigger().setlevelStart(); //make the level -> 1
					m_board.getDigger().setStartLife(); //make the life -> 3
					m_board.getDigger().setStartScore(); //make the score -> 0
					m_board.getDigger().setStartRocks();
					Diamond::setToZero();
					return false;
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				if (isMouseOver(window, m_board.getMenu().getStartIcon()))
					m_board.getMenu().setStartIconBound(sf::Color::Magenta);
				else
					m_board.getMenu().setStartIconBound(sf::Color::White);

				if (isMouseOver(window, m_board.getMenu().getQuitIcon()))
					m_board.getMenu().setQuitIconBound(sf::Color::Magenta);
				else
					m_board.getMenu().setQuitIconBound(sf::Color::White);
			}
		}
	}

	return true;
}

void Controller::timeFunc() //decrease one second from game clock
{
	m_gameTime = m_gameClock.getElapsedTime();

	if (m_gameTime.asSeconds() > 1)
	{
		m_board.getDigger().setTime(-1);
		m_gameClock.restart();
	}
}
