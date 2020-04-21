#include "pch.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, 
	float offset_x, float offset_y, float width, float height)
	: sprite(sprite), offsetx(offset_x), offsety(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x , this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Transparent);
}

HitboxComponent::~HitboxComponent()
{

}

//accessors
const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

//Modifiers
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetx, position.y - this->offsety);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetx, y - this->offsety);
}

//functions

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetx, this->sprite.getPosition().y + this->offsety); //will keep its size
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
