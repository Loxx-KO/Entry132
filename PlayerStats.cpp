#include "pch.h"
#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
}

PlayerStats::PlayerStats(int hp, int defence, int baseDmg, int maxDmg, int mana, int exp)
{
	this->hp = hp;
	this->defence = defence;
	this->baseDmg = baseDmg;
	this->maxDmg = maxDmg;
	this->mana = mana;
	this->exp = exp;
}

PlayerStats::~PlayerStats()
{

}
