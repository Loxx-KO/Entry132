#include "pch.h"
#include "Bar.h"

Bar::Bar(float x, float y, float width, float height, sf::Texture* texture_bg)
{
	this->bar_bg.setSize(sf::Vector2f(width, height));
	this->bar_bg.setPosition(sf::Vector2f(x, y));
	this->bar_bg.setTexture(texture_bg);
}

Bar::~Bar()
{

}

void Bar::update()
{
}

void Bar::render(sf::RenderTarget& target)
{
	target.draw(this->bar_bg);
}
