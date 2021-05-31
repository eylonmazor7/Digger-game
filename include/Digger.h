#pragma once
#include"MobileObjects.h"

class Digger : public MobileObjects
{
public:
	Digger() {}
	~Digger() = default;

	virtual sf::Vector2f& setDirection() override;

	virtual void collission(Objects&) override;
	virtual void collission(SmartMonster&) override;
	virtual void collission(StupidMonster&) override;
	virtual void collission(Diamond&) override;
	virtual void collission(Rock&) override;
	virtual void collission(Wall&) override;
	virtual void collission(TimeGift&) override;
	virtual void collission(ScoreGift&) override;
	virtual void collission(LifeGift&) override;

	virtual void collission(Digger&) override {}

	int getScore() const;
	void setScore(int);
	int getLevel() const;
	void setLevel(int);
	int getRocks() const;
	void setRocks(int);
	int getLife() const;
	void setLife(int);
	int getTime() const;
	void setTime(int);
	
	void setTimeStart();
	void setStartLife();
	void setlevelStart();
	void setStartScore();
	void setStartRocks();


	static sf::Vector2f digPos();
	static void setStaticDigPos(sf::Vector2f&);

private:
	static sf::Vector2f m_myPos;
	int m_life = 3;
	int m_score = 0;
	int m_level = 0;
	int m_rocksAllowed = 0;
	int m_time = 0;

};