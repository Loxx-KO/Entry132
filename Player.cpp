#include "pch.h"
#include "Player.h"

//initializer functions
void Player::initializeVariables()
{
	this->hp = hp;
	this->mana = mana;
}

void Player::initializeComponents()
{

}

Player::Player(float x, float y, sf::Texture& sprite_sheet)
{
	this->initializeVariables();

	this->setPosition(x, y);

	this->createMovementComponent(130.f, 9.f, 3.f);
	this->createHitboxComponent(this->sprite, 15.f, 10.f, 35.f, 90.f);
	this->createAnimationComponent(sprite_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 12.f, 0 , 0, 13, 0, 66, 100);
}

Player::~Player()
{

}

//accessors

//functions

void Player::update(const float& dtime)
{
	this->movementComponent->update(dtime);
	this->animationComponent->play("IDLE_LEFT", dtime);
	this->hitboxComponent->update();
}
