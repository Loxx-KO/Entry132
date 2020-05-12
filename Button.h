#pragma once
#include "pch.h"

enum button_states		//list of values for button states
{
	BUTTON_IDLE = 0,
    BUTTON_HOVER,
	BUTTON_PRESSED
};

class Button
{
private:
	//button state
	short unsigned buttonState;

	float buttonTime;
	float buttonTimeMax;

	sf::RectangleShape buttonshape;
	sf::Font* font;
	sf::Text buttontext;

	//text's look

	unsigned fontSize;
	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	//button's look
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;

public:
	Button(float x, float y, float width, float height, 
		sf::Font* font, std::string text, unsigned font_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();
	//accessors
	const bool isPressed() const;					//checks if button is pressed
	const bool getButtonTime();

	//functions
	virtual void updateButtonTime(const float& dtime);
	void update(const sf::Vector2f& mousePosition);
	void render(sf::RenderTarget& target);
};
