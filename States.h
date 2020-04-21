#pragma once

//later also for loading textures nstuff (resorces for the game)

#include "pch.h"
#include "Player.h"
#include "Enemy.h"

class States
{
private:

protected:
	std::stack<States*>* states;			//pointer to the orginal stack of pointers(states)

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool end;
	bool paused;
	float keytime;
	float keytimemax;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;		
	sf::Vector2f mousePositionView;			

	//resorces 
	std::map<std::string ,sf::Texture> textures;

	//functions
	virtual void initializeKeybinds() = 0; //each state has to define them

public:

	States(sf::RenderWindow* window, std::map<std::string,int>* supportedKeys, std::stack<States*>* states);
	virtual ~States();

	//accessors
	const bool& getEnd() const;
	const bool getKeyTime();									// add & if neccessary

	//functions
	void endState();

	void pauseState();
	void unPausedState();

	virtual void updateKeyTime(const float& dtime);
	virtual void updateMousePositions();
	virtual void updateInput(const float& dtime) = 0;
	virtual void update(const float& dtime) = 0;				 //pure virtual, base class, makes sure that child class uses those functions
	virtual void render(sf::RenderTarget* target = nullptr) = 0; //also for specyfic targets
};

