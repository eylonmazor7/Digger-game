#pragma once
#include "Objects.h"
#include "Toolbar.h"
#include "Menu.h"
#include "StaticObjects.h"
#include "StupidMonster.h"
#include "SmartMonster.h"
#include "Digger.h"
#include "MobileObjects.h"
#include "Monster.h"
#include "Gift.h"
#include "Diamond.h"
#include "Wall.h"
#include "Rock.h"
#include <memory>
#include <LifeGift.h>
#include <TimeGift.h>
#include <ScoreGift.h>
#include <fstream>

class Board
{
public:
	Board(); //constructor
	~Board(); 

	bool readBoard(); 
	Menu& getMenu();
	Toolbar& getToolbar();
	Digger& getDigger(); 

	int getRocksAllowed();

	void restartStaticPos(); 
	void restartMobilePos();
	void setFilePointer(); //set mark in case of restart level
	void loadTextures(); //private
	void drawStatics(sf::RenderWindow&);
	void drawMonsters(sf::RenderWindow&);
	void drawDigger(sf::RenderWindow&);
	void moveObjects();
	void checkCollisions();
	void cleanVectors();
	void checkIfWrongMove();
	int getTime(); //const

	std::vector <sf::Texture> getTextureVec();

	static int getRows();
	static int getCols();

private:

	Digger m_digger;
	Toolbar m_toolbar;
	Menu m_menu;

	std::ifstream myfile;
	std::vector <sf::Texture> m_textureVec;
	std::vector <std::string> m_picNameVec;
	std::vector <std::unique_ptr<StaticObjects>> m_staticObject;
	std::vector <std::unique_ptr<Monster>> m_monster;

	int m_rocksAllowed;
	int m_time = 0;
	int m_fileLocation;
	int m_rowSize;
	int m_colSize;
	
	static int m_rows;
	static int m_cols;
};
