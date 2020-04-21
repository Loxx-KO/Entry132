#pragma once
// game "engine" class

#include "pch.h"
#include "MainMenuState.h"
#include "SettingsState.h"

class Game
{

private:
	//variables
	sf::RenderWindow *window;
	sf::Event Events;
	std::vector<sf::VideoMode> VideoModes;
	sf::ContextSettings window_settings;
	bool fullscreen;

	sf::Clock dtClock;
	float dtime;

	std::stack<States*> states;					//States is abstract - must be a pointer (we will have a few states), for updating states of the game

	std::map<std::string, int> supportedKeys;

	//functions
	void initializeVariables();
	void initializeWindow();
	void initalizeKeys();
	void initalizeStates();

public:
	Game();
	virtual ~Game();

	//functions
	void endGameApp();

	//updating
	void updateDt();
	void updateSFMLevents();	//ctrl + . to create declaration in cpp file
	void update();

	//rendering
	void render();

	void run();

};


