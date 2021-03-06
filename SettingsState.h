#pragma once
#include "States.h"
#include "Button.h"

class SettingsState :
	public States
{
private:

	//variables
	sf::Texture bgimage;
	sf::RectangleShape background;
	sf::Font font;
	bool fullscreen;

	std::map<std::string, Button*> buttons;

	//functions
	void initializeVariables();
	void initializeBackground();
	void initializeFonts();
	void initializeKeybinds();
	void initializeButtons();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//functions

	void updateInput(const float& dtime);
	void updateButtons();
	void update(const float& dtime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

