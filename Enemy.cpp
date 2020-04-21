#include "pch.h"
#include "Enemy.h"

void Enemy::initializeVariables()
{

}

Enemy::Enemy(float x, float y, sf::Texture& texture)
{
	this->initializeVariables();

	this->createMovementComponent(0.f, 0.f, 0.f);
	this->createHitboxComponent(this->sprite, 0.f, 0.f, 70.f, 100.f);

	this->setTexture(texture);
	this->setPosition(x,y);
}

Enemy::~Enemy()
{

}

//accessors
const sf::FloatRect Enemy::CreateEnemyBox() const
{
	return this->getGlobalBounds();
}

//functions
void Enemy::update(const float& dtime)
{
	this->movementComponent->update(dtime);
	this->hitboxComponent->update();
}