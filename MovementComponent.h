#pragma once

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
	const sf::Vector2f& getSpeed() const;

	//functions
	void move(const float x, const float y, const float& dtime);
	void stopMovement();
	void stopMovementX();
	void stopMovementY();
	void update(const float& dtime);
};

