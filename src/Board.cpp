#include "Board.h"
#include <fstream>


int Board::m_rows = 0;
int Board::m_cols = 0;

Board::Board()
{
	m_picNameVec = { "digger.png", "mewoth6.png", "waba2.png", "diamond2.png", "rock.png", "wall.png", "gift2.png" };
	m_fileLocation = 0;
	myfile.open("Board.txt"); //file to read from
	//myfile.open("Board2.txt"); //file to read from

	if (myfile.fail())
	{
		std::cout << "open file failed()\n";
		exit(EXIT_FAILURE);
	}
}

Board::~Board()
{
	myfile.close();
}

void Board::loadTextures() //load textures for all objects
{
	m_textureVec.resize(7);
	for (int i = 0; i < 7; i++)
	{
		m_textureVec[i].loadFromFile(m_picNameVec[i]);
		m_textureVec[i].setSmooth(true);
	}
}

bool Board::readBoard()
{
	int n; //n for rand
	
	if (!(myfile >> m_rows >> m_cols >> m_rocksAllowed >> m_time)) //if there is no more levels - return false;
		return false;

	myfile.get(); //"eat" the \n

	m_rowSize = 700 / m_rows;
	m_colSize = 1200 / m_cols;

	//all 5 details displayed during game
	m_digger.setRocks(m_rocksAllowed);
	m_digger.setTimeStart();
	m_digger.setTime(m_time);
	m_digger.setLevel(1);
	m_digger.setScore(0);

	for (int ROWS = 0; ROWS < m_rows; ROWS++)
	{
		for (int COLS = 0; COLS < m_cols; COLS++)
		{
			sf::Vector2f pos; //set onject position
			pos.x = COLS * m_colSize;
			pos.y = ROWS * m_rowSize;

			char c;
			myfile.get(c);

			switch (c)
			{
			case '/': //digger object
				m_digger.setCurrPos(pos);
				m_digger.setStaticDigPos(pos);
				m_digger.setStartPos(pos);
				m_digger.setChar('/');
				m_digger.getRec().setSize(sf::Vector2f(m_rowSize - 5, m_rowSize - 5));
				m_digger.setTex(m_textureVec[0]);
				break;

			case '!': //monster object

				if (rand() % 2) //determine smart or stupid monster
					m_monster.push_back(std::make_unique<SmartMonster>(pos, '!', m_textureVec[1]));
				else 
					m_monster.push_back(std::make_unique<StupidMonster>(pos, '?', m_textureVec[2]));
				break;

			case '+': //gift object
				n = rand() % 3; //determine which gift type - time, score or life

				if(n == 0 && m_time > 0)
					m_staticObject.push_back(std::make_unique<TimeGift>(pos, '+'));
				else if(n == 1)
					m_staticObject.push_back(std::make_unique<ScoreGift>(pos, '+'));
				else
					m_staticObject.push_back(std::make_unique<LifeGift>(pos, '+'));
				
				break;

			case 'D': //diamond object
				m_staticObject.push_back(std::make_unique<Diamond>(pos, 'D')); break;
			case '#': //wall object
				m_staticObject.push_back(std::make_unique<Wall>(pos, '#')); break;
			case '@': //rock object
				m_staticObject.push_back(std::make_unique<Rock>(pos, '@')); break;

			default: continue;
			}

		}
		myfile.get(); //"eat" the \n
	}
	myfile.get(); //"eat" the \n
	for (int i = 0; i < m_monster.size(); i++)
		m_monster[i]->setRecSize(sf::Vector2f(m_rowSize - 5, m_rowSize - 5));

	return true;
}

void Board::drawStatics(sf::RenderWindow& window) //draw all static objects on window
{
	sf::RectangleShape rec;
	rec.setSize(sf::Vector2f(m_colSize, m_rowSize));
	rec.setOutlineColor(sf::Color::Transparent);
	sf::Vector2f pos;

	char c;
	for (int i = 0; i < m_staticObject.size(); i++)
	{
		if (!(m_staticObject[i]->getExist())) //if this object is no need in this specific case.
			continue;

		pos = m_staticObject[i].get()->getStartPos();
		rec.setPosition(pos.x,pos.y);
		c = m_staticObject[i]->getChar();
		
		switch (c) //set textures as apropriate
		{
		case 'D': rec.setTexture(&m_textureVec[3]); break;
		case '@': rec.setTexture(&m_textureVec[4]); break;
		case '#': rec.setTexture(&m_textureVec[5]); break;
		case '+': rec.setTexture(&m_textureVec[6]); break;
		default: break;
		}

		window.draw(rec);
	}
}

void Board::drawMonsters(sf::RenderWindow& window) //draw all monsters on the window
{
	sf::Vector2f pos;
	for (int i = 0; i < m_monster.size(); i++)
	{
		pos = m_monster[i]->getCurrPos();
		m_monster[i]->getRec().setPosition(pos.x, pos.y);
		window.draw(m_monster[i]->getRec());
	}
}

void Board::drawDigger(sf::RenderWindow& window) //draw digger on window
{
	sf::Vector2f pos;
	pos = m_digger.getCurrPos();
	m_digger.getRec().setPosition(pos.x, pos.y);
	window.draw(m_digger.getRec());
}

void Board::moveObjects() //move all mobile objects
{
	m_digger.moveObjects();
	
	for (int i = 0; i < m_monster.size(); i++)
		m_monster[i]->moveObjects();
}

int Board::getRows()
{
	return m_rows;
}

int Board::getCols()
{
	return m_cols;
}

void Board::checkCollisions() //check collision for all objects- double dispatch
{
	sf::RectangleShape rec;
	rec.setSize(sf::Vector2f(m_rowSize - 5, m_rowSize - 5));//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	for (int i = 0; i < m_staticObject.size(); i++) //digger <----> statics
	{
		rec.setPosition(m_staticObject[i]->getStartPos());
		if (m_staticObject[i]->getExist() && m_digger.getRec().getGlobalBounds().intersects(rec.getGlobalBounds()))
		{
			m_digger.collission(*m_staticObject[i]);
			break;
		}
	}

	for (int i = 0; i < m_monster.size() ; i++) //digger <----> Monsters
	{
		if (m_digger.getRec().getGlobalBounds().intersects(m_monster[i]->getRec().getGlobalBounds()))
		{
			m_digger.collission(*m_monster[i]);
			break;
		}
	}

	for (int i = 0; i < m_monster.size(); i++) // Monsters <----> statics
	{
		for (int j = 0; j < m_staticObject.size(); j++)
		{
			if (!(m_staticObject[j]->getExist())) //this static doesn't exist
				continue;

			rec.setPosition(m_staticObject[j]->getStartPos());
			if (m_monster[i]->getRec().getGlobalBounds().intersects(rec.getGlobalBounds()))
				m_monster[i]->collission(*m_staticObject[j]);
		}
	}
}

int Board::getRocksAllowed()
{
	return m_rocksAllowed;
}

void Board::restartStaticPos() //set all static objects back to exist
{
	for (int i = 0; i < m_staticObject.size(); i++)
		m_staticObject[i]->setExist(true);
}

void Board::restartMobilePos() //restart all mobile objects positions
{
	for (int i = 0; i < m_monster.size(); i++)
		m_monster[i]->setCurrPos(m_monster[i]->getStartPos());

	m_digger.setCurrPos(m_digger.getStartPos());
}

void Board::setFilePointer() //in case of reading file again
{
	myfile.clear();
	myfile.seekg(0);
}

void Board::cleanVectors() //delete all objects except of digger
{
	m_monster.clear();
	m_staticObject.clear();
}

Menu& Board::getMenu()
{
	return m_menu;
}

Toolbar& Board::getToolbar()
{
	return m_toolbar;
}

Digger& Board::getDigger()
{
	return m_digger;
}

std::vector <sf::Texture> Board::getTextureVec()
{
	return m_textureVec;
}

void Board::checkIfWrongMove() //check if move is legal
{
	if (m_digger.getBool())
		m_digger.itsWrongMove();

	for (int i = 0; i < m_monster.size(); i++)
		if (m_monster[i]->getBool())
			m_monster[i]->itsWrongMove();
}

int Board::getTime()
{
	return m_time;
}
