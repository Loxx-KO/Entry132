#pragma once
#include "Entity.h"

enum STATUS
{
	INGAME = 0,
	INFIGHT
};

//zrob tez enum dla enemyname by pominac te wszystkie ify

struct Enemy :
	public Entity
{
private:
	//variables
	std::string name;
	int hp;
	int exp;
	int baseDmg;
	int maxDmg;

	//initialize functions
	void initializeVariables();

public:

	Enemy(float x, float y, sf::Texture& texture, std::string name, const short unsigned STATE);
	virtual ~Enemy();

	//accessors
	const sf::FloatRect CreateEnemyBox() const;
	const int getEnemyHP() const;
	const int getEnemyBaseDMG() const;
	const int getEnemyMaxDMG() const;
	const int getEnemyExp() const;
	const std::string getName() const;

	//functions
	virtual void update(const float& dtime);

};

