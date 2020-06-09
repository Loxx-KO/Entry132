#pragma once

//loading textures nstuff (resorces for the game), states stack etc

#include "pch.h"
#include "Player.h"
#include "Enemy.h"
#include "GraphicsSettings.h"

class GraphicsSettings;
class States;

class StateData
{
public:

	//variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<States*>* states;

	StateData()
	{
		this->gridSize = NULL;
		this->window = NULL;
		this->gfxSettings = NULL;
		this->supportedKeys = NULL;
		this->states = NULL;
	};
};

class States
{
private:

protected:
	StateData* stateData;
	std::stack<States*>* states;			//pointer to the orginal stack of pointers(states)

	sf::RenderWindow* window;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	bool end;
	bool paused;
	bool fight;

	float keytime;
	float keytimemax;
	float gridSize;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;		
	sf::Vector2f mousePositionView;	
	sf::Vector2u mousePositionGrid;

	//resorces 
	std::map<std::string ,sf::Texture> textures;

	//functions
	virtual void initializeKeybinds() = 0; //each state has to define them

public:

	States(StateData* state_data);
	virtual ~States();

	//accessors
	const bool& getEnd() const;
	const bool getKeyTime();				// add & if neccessary

	//functions
	void endState();

	void pauseState();
	void unPausedState();

	void fightStateNotActive();
	void fightStateEnding();

	virtual void updateKeyTime(const float& dtime);

	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateInput(const float& dtime) = 0;
	virtual void update(const float& dtime) = 0;				 //pure virtual, base class, makes sure that child class uses those functions
	virtual void render(sf::RenderTarget* target = nullptr) = 0; //also for specyfic targets
};

