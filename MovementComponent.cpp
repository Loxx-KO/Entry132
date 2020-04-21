#include "pch.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxspeed,
	float acceleriation, float deceleration)
	: sprite(sprite), maxspeed(maxspeed),
	acceleriation(acceleriation), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//accessors
const sf::Vector2f& MovementComponent::getSpeed() const
{
	return this->speed;
}

//functions
void MovementComponent::move(const float x, const float y, const float& dtime)
{
	//acceleration

	if (this->speed.x > 0.f) //check for right
	{
		if (this->speed.x > this->maxspeed)
		{
			this->speed.x = this->maxspeed;
		}
	}
	else if (this->speed.x < 0.f) //check for left
	{
		if (this->speed.x < (-1) * this->maxspeed)
		{
			this->speed.x = (-1) * this->maxspeed;
		}
	}
	this->speed.x += this->acceleriation * x;
	
	if (this->speed.y > 0.f) //up
	{
		if (this->speed.y > this->maxspeed)
		{
			this->speed.y = this->maxspeed;
		}
	}
	else if (this->speed.y < 0.f) //down
	{
		if (this->speed.y < (-1) * this->maxspeed)
		{
			this->speed.y = (-1) * this->maxspeed;
		}
	}
	this->speed.y += this->acceleriation * y;
}

void MovementComponent::stopMovement()
{
	//resets speed to 0

	this->speed.x = 0.f;
	this->speed.y = 0.f;
}

void MovementComponent::stopMovementX()
{
	this->speed.x = 0.f;
}

void MovementComponent::stopMovementY()
{
	this->speed.y = 0.f;
}

void MovementComponent::update(const float& dtime)
{
	//deceleration
	if (this->speed.x > 0.f)
	{
		this->speed.x -= deceleration;
		if (this->speed.x < 0.f)
		{
			this->speed.x = 0.f;
		}
	}
	else if (this->speed.x < 0.f)
	{
		this->speed.x += deceleration;
		if (this->speed.x > 0.f)
		{
			this->speed.x = 0.f;
		}
	}

	if (this->speed.y > 0.f)
	{
		this->speed.y -= deceleration;
		if (this->speed.y < 0.f)
		{
			this->speed.y = 0.f;
		}
	}
	else if (this->speed.y < 0.f)
	{
		this->speed.y += deceleration;
		if (this->speed.y > 0.f)
		{
			this->speed.y = 0.f;
		}
	}

	//final move
	this->sprite.move(this->speed * dtime);
}
