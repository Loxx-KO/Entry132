#pragma once
#include "GameState.h"
#include "Button.h"
#include "EditorState.h"

class MainMenuState :
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
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states);
	virtual ~MainMenuState();

	//functions

	void updateInput(const float& dtime);
	void updateButtons();
	void update(const float& dtime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

