#pragma once
// game "engine" class

#include "pch.h"
#include "MainMenuState.h"
#include "SettingsState.h"
#include "GraphicsSettings.h"

class Game
{

private:

	//variables
	GraphicsSettings graphicSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event Events;

	sf::Clock dtClock;
	float dtime;

	std::stack<States*> states;					//States is abstract - must be a pointer (we will have a few states), for updating states of the game

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//functions
	void initializeVariables();
	void initializeGraphicSettings();
	void initializeWindow();
	void initalizeKeys();
	void initializeStateData();
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


