#pragma once
#include "Entity.h"

struct Enemy :
	public Entity
{
private:
	//variables

	//initialize functions
	void initializeVariables();

public:

	Enemy(float x, float y, sf::Texture& texture);
	virtual ~Enemy();


	//accessors
	const sf::FloatRect CreateEnemyBox() const;

	//functions
	void update(const float& dtime);

};

