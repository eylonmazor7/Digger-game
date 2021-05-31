#pragma once
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class Options //enum to determine which situation are we in
{
	RocksStackDone,
	GameOver, 
	NextLevel,
	RestartMobile,
	TimesUp,
	Nothing
};

class Controller
{
public:
	Controller();
	~Controller() = default;
	void run();

	void startMenuFunc(sf::RenderWindow& window);
	void drawBoard(sf::RenderWindow&);
	bool isMouseOver(sf::RenderWindow& window, sf::RectangleShape shape);

	void checkGame(sf::RenderWindow&, bool&, bool&);
	Options checkGameRules();
	bool endGameMenuWin(sf::RenderWindow&);
	bool endGameMenuLost(sf::RenderWindow&);
	void restartLevelFunc();
	void timeFunc();

	static void setBool();
	static float getDt();

private:

	sf::Texture m_tex;
	sf::RectangleShape m_bgPic;
	sf::Font m_font;
	sf::Music m_music;
	sf::Clock m_deltaTime;
	sf::Clock m_gameClock;
	sf::Time m_gameTime;

	std::vector<sf::RectangleShape> m_Toolbar;
	
	Board m_board;

	static float dt;
	static bool DiggerMonsterCollision;
};