#pragma once
#include "Entity.h"

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

	Enemy(float x, float y, sf::Texture& texture, std::string name);
	virtual ~Enemy();

	//accessors
	const sf::FloatRect CreateEnemyBox() const;
	const int getEnemyHP() const;
	const int getEnemyBaseDMG() const;
	const int getEnemyMaxDMG() const;
	const int getEnemyExp() const;
	const std::string getName() const;

	//functions
	void update(const float& dtime);

};
