#pragma once
#include "Objects.h"

class StaticObjects : public Objects
{
public:
	using Objects::Objects; //using object constructor
	~StaticObjects() = default;

	void setExist(bool); //set existance of a static object
	bool getExist() const;

	virtual void collission(Objects&) = 0;
	virtual void collission(Digger& other) = 0;
	virtual void collission(SmartMonster&) = 0;
	virtual void collission(StupidMonster&) = 0;
	virtual void collission(Diamond&) = 0;
	virtual void collission(Rock&) = 0;
	virtual void collission(Wall&) = 0;
	virtual void collission(TimeGift&) = 0;
	virtual void collission(ScoreGift&) = 0;
	virtual void collission(LifeGift&) = 0;

private:
	bool m_exist = true;

};