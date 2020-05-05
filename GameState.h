#pragma once

#include "pch.h"
#include "States.h"
#include "PausedMenu.h"
#include "FightState.h"
#include "SettingsState.h"

class GameState :
	public States
{
private:
	sf::Font font;
	PausedMenu* pausemenu;
	FightState* fight;

	Player* player;

	//enemies
	Enemy* testenemy;
	Enemy* blob;
	Enemy* snake;

	Enemy* activeEnemy;

	std::vector<Enemy*> activeEnemies;
	std::string enemyName;

	//collision stuff
	sf::FloatRect playerbox;
	sf::FloatRect enemybox;

	//functions
	void initializeVariables();
	void initializeKeybinds();
	void initializeFonts();
	void initializeTextures();
	void initializePauseMenu();
	void initializeFight();
	void initializeEnemy();
	void CreateEnemy();
	void initializePlayers();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states);
	virtual ~GameState();

	//functions
	void updateInput(const float& dtime);
	void updatePausedInput(const float& dtime);
	void checkForCollision(const float& dtime);
	void updatePausedMenuButtons();
	void update(const float& dtime);
	void render(sf::RenderTarget* target = nullptr);
	//nullptr - deafult argument, nullptr will appear only here
};

