#pragma once

#include "pch.h"
#include "States.h"
#include "PausedMenu.h"
#include "FightState.h"
#include "SettingsState.h"
#include "TileMap.h"
#include "PlayerStats.h"

class GameState :
	public States
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PausedMenu* pausemenu;

	Player* player;
	//PlayerStats player_stats;
	int hp;
	int defence;
	int baseDmg;
	int maxDmg;
	int mana;
	int exp;
	int lvl;

	int dead;

	//enemies
	std::vector<Enemy*> activeEnemies;
	std::string enemyName;

	//collision stuff
	sf::FloatRect playerbox;
	sf::FloatRect enemybox;

	//map
	TileMap* tileMap;

	//functions
	void initializeDeferredRender();
	void initializeVariables();
	void initializeView();
	void initializeKeybinds();
	void initializeFonts();
	void initializeTextures();
	void initializePauseMenu();
	void initializeTileMap();
	void initializeEnemy();
	void initializePlayers();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//functions
	void deleteEnemy(int i);
	void updateInput(const float& dtime);
	void updatePausedInput(const float& dtime);
	void checkForCollision(const float& dtime);
	void updateView(const float& dtime);
	void updatePausedMenuButtons();
	void update(const float& dtime);
	void render(sf::RenderTarget* target = nullptr);
	//nullptr - deafult argument, nullptr will appear only here
};

