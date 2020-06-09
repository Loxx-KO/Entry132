#pragma once
#include "Button.h"

class TextureSelector
{
private:
	float gridSize;

	bool active;
	bool hidden;
	Button* hide_button;
	const float keyTimeMax;
	float keyTime;

	sf::RectangleShape bounds;
	sf::Sprite sheet;
	sf::RectangleShape selector;
	sf::Vector2u mousePosGrid;
	sf::IntRect textureRect;

public:
	TextureSelector(float x, float y, float width, float heigth, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string button_text);
	~TextureSelector();

	//accessors
	const bool& getActive() const;
	const sf::IntRect& getTextureRect() const;
	const bool getKeyTime();

	//functions
	void updateKeyTime(const float& dtime);
	void update(const sf::Vector2i& mousePosWindow, const float& dtime);
	void render(sf::RenderTarget& target);
};

