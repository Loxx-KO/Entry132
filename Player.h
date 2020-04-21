#pragma once
#include "Entity.h"

struct Player :
	public Entity
{
private:
	//variables
	float hp;
	float mana;

	//initialize functions
	void initializeVariables();
	void initializeComponents();

public:

	Player(float x, float y, sf::Texture& sprite_sheet);
	virtual ~Player();

	//accessors

	//functions
	virtual void update(const float& dtime);
};

