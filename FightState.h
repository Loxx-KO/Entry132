#pragma once
#include "pch.h"
#include "States.h"
#include "Button.h"
#include "Bar.h"

class FightState :
	public States
{
private:
	//buttons
	sf::Texture bgimage;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//player
	Player* player_fight;

	int playerHpTemp;
	int playerHp;
	int playerDef;
	int playerMana;
	int playerDMG;
	int playerExp;

	bool playerdead;
	float playerBarWidth;
	
	//enemy
	int enemyCount = 1;

	Enemy** enemies;
	std::vector<Enemy*> currentEnemies;

	int enemyHpTemp;
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
	FightState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states, Enemy* enemy, std::string enemyName);
	virtual ~FightState();

	//accessors

	//functions

	void enemyAttack();
	void attack();
	void defend();
	void useItem();
	void tryRun();
	void checkIfAnyoneDead();
	
	void changeBarSize();

	void updateInput(const float& dtime);
	void updateButtons();
	void update(const float& dtime);

	void sleepFor();
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

