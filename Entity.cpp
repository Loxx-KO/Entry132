#include "pch.h"
#include "Entity.h"

void Entity::initializeVariables()
{
	this->movementComponent = NULL;
	this->hitboxComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initializeVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
}

//component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxspeed,
	const float acceleriation, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxspeed, acceleriation, deceleration);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, 
	float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createAnimationComponent(sf::Texture& sprite_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, sprite_sheet);
}

const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite.getPosition();
}

//accessors
const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f& Entity::getMovementSpeed() const
{
	return this->movementComponent->getSpeed();
}

//functions
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
	{
		this->hitboxComponent->setPosition(x, y);
	}
	this->sprite.setPosition(x,y);
}

void Entity::move(const float x, const float y, const float& dtime)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(x,y, dtime);
	}
}

void Entity::stopSpeed()
{
	if (this->movementComponent)
		this->movementComponent->stopMovement();

}

void Entity::stopSpeedX()
{
	if (this->movementComponent)
		this->movementComponent->stopMovementX();
}

void Entity::stopSpeedY()
{
	if (this->movementComponent)
		this->movementComponent->stopMovementY();
}

void Entity::update(const float& dtime)
{

}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
	{
		this->hitboxComponent->render(target);
	}
}

void Entity::renderenemy(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
	{
		this->hitboxComponent->render(target);
	}
}
