#pragma once
#include "pch.h"
#include "States.h"
#include "Button.h"
#include "Bar.h"
#include "PlayerStats.h"

class FightState :
	public States
{
private:
	//buttons
	sf::Texture bgimage;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	float keytime;
	const float keytimeMax;

	//player
	//PlayerStats player_stats;
	Player* player_fight;

	int playerHp;
	int playerDef;
	int playerMana;
	int playerMaxDMG;
	int playerBaseDMG;
	int playerDMG;
	int playerCurrentExp;
	int playerExp;
	int playerLvl;

	int playerdead;
	float playerBarWidth;
	
	//enemy
	int enemyCount = 1;

	Enemy** enemies;
	std::vector<Enemy*> currentEnemies;

	std::string enemyName;
	int enemyHp;
	int enemyDMG;
	int enemyExp;
	int runChance;

	float enemyBarWidth;

	//others
	bool enemydead;
	int gainEXP;
	bool turn;

	//bars
	Bar* playerBar;

	sf::Texture hpBarPlayer;
	sf::RectangleShape PlayerBarHp;

	Bar* enemyBar;

	sf::Texture hpBarEnemy;
	sf::RectangleShape enemyBarHp;

	//functions
	void initializeVariables();
	void initializeTextures();
	void initializePlayer();
	void initializeBackground();
	void initializeFonts();
	void initializeKeybinds();
	void initializeButtons();
	void initializeBars();

public:
	FightState(StateData* state_data, Enemy* enemy, std::string enemyName);
	virtual ~FightState();

	//accessors
	const bool getKeyTime();

	//functions

	void enemyAttack();
	void attack();
	void defend();
	void useItem();
	void tryRun();
	void checkIfAnyoneDead();
	void lvlUp();
	
	void changeBarSize();

	void updateInput(const float& dtime);
	void updateKeyTime(const float& dtime);
	void updateButtons(const float& dtime);
	void update(const float& dtime);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

