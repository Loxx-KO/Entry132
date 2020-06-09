#pragma once
//character etc
#include "pch.h"
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initializeVariables();

protected:								//inbetween private and public
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	HitboxComponent* hitboxComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	//component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxspeed,
		const float acceleriation, const float deceleration);
	void createHitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, float width, float height);
	void createAnimationComponent(sf::Texture& sprite_sheet);

	//accessors
	virtual const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f& getMovementSpeed() const;

	//functions
	virtual void setPosition(const float x, const float y);

	virtual void move(const float x, const float y, const float& dtime);
	virtual void stopSpeed();
	virtual void stopSpeedX();
	virtual void stopSpeedY();

	virtual void update(const float& dtime);
	virtual void render(sf::RenderTarget& target);
	virtual void renderenemy(sf::RenderTarget& target);
};

