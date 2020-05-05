#pragma once
#include "Entity.h"

struct Player :
	public Entity
{
private:
	//variables
	int hp;
	int defence;
	int dmg;
	int baseDmg;
	int maxDmg;
	int mana;
	int exp;
	std::string state;

	//initialize functions
	void initializeVariables();
	void initializeComponents();

public:

	Player(float x, float y, sf::Texture& sprite_sheet, std::string state);
	virtual ~Player();

	//accessors
	const int getStatsHP() const;
	const int getStatsDefence() const;
	const int getStatsBaseDMG() const;
	const int getStatsMaxDMG() const;
	const int getStatsMana() const;
	const int getStatsExp() const;

	//functions
	virtual void update(const float& dtime);
};

