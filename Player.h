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
	bool dead;

	std::string state;
	std::string name;

	bool idle;

	//initialize functions
	void initializeVariables();
	void initializeComponents();

public:

	Player(float x, float y, sf::Texture& sprite_sheet, std::string state);
	virtual ~Player();

	//functions
	void loadStatsFromFile(const std::string file_name, int& Hp, int& Defence, int& BaseDmg, int& MaxDmg, int& Mana, int& Exp, int& Lvl, int& ifdead);
	void saveStatsToFile(const std::string file_name, int Hp, int Defence, int BaseDmg, int MaxDmg, int Mana, int Exp, int Lvl, int ifdead);
	virtual void update(const float& dtime);
};

