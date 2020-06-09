#pragma once
#include "States.h"
#include "Button.h"
#include "GameState.h"
#include "MainMenuState.h"

class GameOver :
	public States
{
private:
	//variables
	sf::Texture bgimage;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//functions
	void initializeVariables();
	void initializeBackground();
	void initializeFonts();
	void initializeKeybinds();
	void initializeButtons();

public:
	GameOver(StateData* state_data);
	virtual ~GameOver();

	//functions

	void updateInput(const float& dtime);
	void updateButtons();
	void update(const float& dtime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

