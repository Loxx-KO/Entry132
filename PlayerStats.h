#pragma once
class PlayerStats
{
protected:
	int hp = 0;
	int defence = 0;
	int baseDmg = 0;
	int maxDmg = 0;
	int mana = 0;
	int exp = 0;
public:
	PlayerStats();
	PlayerStats(int hp, int defence, int baseDmg, int maxDmg, int mana, int exp);
	virtual ~PlayerStats();
};

