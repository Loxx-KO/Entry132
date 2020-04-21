#pragma once
#include "Button.h"

class PausedMenu
{
private:
	sf::Font& font;					//& <- to force the font - its needed to create the paused menu
	sf::Text menutext;

	sf::RectangleShape background;
	sf::RectangleShape box;			//button box

	std::map<std::string, Button*> buttons;

	//private functions

public:
	PausedMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PausedMenu();

	//accessors
	std::map<std::string, Button*>& getButtons();

	//functions
	void addButton(const std::string  key, float x, float y, const std::string text);
	const bool isButtonPressed(const std::string key);
	void update(const sf::Vector2f mousePosition);
	void render(sf::RenderTarget& target);
};

