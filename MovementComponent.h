#pragma once

enum MovementStates
{
	IDLE = 0,
	MOVING,
	MOVINGLEFT,
	MOVINGRIGHT,
	MOVINGUP,
	MOVINGDOWN,
};

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxspeed;
	float acceleriation;
	float deceleration;

	sf::Vector2f speed;

	//init functions

public:
	MovementComponent(sf::Sprite& sprite, float maxspeed, 
		float acceleriation, float deceleration);
	virtual ~MovementComponent();

	//accessors
	const float& getMaxSpeed() const;
	const sf::Vector2f& getSpeed() const;

	//functions
	const bool getMoveState(const short unsigned state) const;

	void move(const float x, const float y, const float& dtime);
	void stopMovement();
	void stopMovementX();
	void stopMovementY();
	void update(const float& dtime);
};

