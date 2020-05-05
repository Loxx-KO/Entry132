#pragma once
#include "States.h"
#include "Button.h"

class FightState :
	public States
{
private:
	//buttons
	sf::Texture bgimage;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//fighting stuff
	Player* player_fight;
	int playerHp;
	int playerDef;
	int playerMana;
	int playerDMG;
	//int playerDmgTaken;
	int playerExp;

	//sf::RectangleShape playerbox;
	//sf::Texture playerTexture;
	//sf::Texture hpBarPlayer;
	//sf::RectangleShape playerBar;
	
	int enemyCount = 1;
	//Enemy** enemies = new Enemy * [this->enemyCount];
	Enemy** enemies;
	int enemyHp;
	int enemyDMG;
	int enemyExp;

	//sf::Texture hpBarEnemy;
	//sf::RectangleShape enemyBar;

	bool dead;
	int gainEXP;

	//functions
	void initializeVariables();
	void initializeTextures();
	void initializePlayer();
	void initializeBackground();
	void initializeFonts();
	void initializeKeybinds();
	void initializeButtons();

public:
	FightState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states, Enemy* enemy, std::string enemyName);
	virtual ~FightState();

	//functions

	void updateInput(const float& dtime);
	void updateButtons();
	void update(const float& dtime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};
