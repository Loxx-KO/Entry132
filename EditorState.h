#pragma once
#include "States.h"
#include "Button.h"

class EditorState :
	public States
{
private:
	//variables
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//functions
	void initializeVariables();
	void initializeBackground();
	void initializeFonts();
	void initializeKeybinds();
	void initializeButtons();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states);
	virtual ~EditorState();

	//functions

	void updateInput(const float& dtime);
	void updateButtons();
	void update(const float& dtime);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};



