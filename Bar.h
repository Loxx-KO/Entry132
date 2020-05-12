#pragma once
#include "pch.h"

class Bar
{
private:
	sf::RectangleShape bar_bg;
	sf::Texture texture_bg;

public:
	Bar(float x, float y, float width, float height, sf::Texture* texture_bg);
	virtual ~Bar();

	void update();
	void render(sf::RenderTarget& target);
};

