#include "pch.h"
#include "Player.h"

//initializer functions
void Player::initializeVariables()
{
	this->hp = 100;
	this->mana = 0;
	this->defence = 2;
	this->baseDmg = 7;
	this->maxDmg = 9;
	this->exp = 0;
}

void Player::initializeComponents()
{

}

Player::Player(float x, float y, sf::Texture& sprite_sheet, std::string state)
{
	this->initializeVariables();

	if (state == "ingame")
	{
		this->setPosition(x, y);

		this->createMovementComponent(130.f, 9.f, 3.f);
		this->createHitboxComponent(this->sprite, 0.f, 0.f, 66.f, 100.f); //15.f, 10.f, 35.f, 90.f
		this->createAnimationComponent(sprite_sheet);

		//animations
		this->animationComponent->addAnimation("IDLE_FRONT", 12.f, 0, 0, 13, 0, 66, 100);
		this->animationComponent->addAnimation("WALK_FRONT", 6.f, 0, 1, 9, 1, 66, 100);

		this->animationComponent->addAnimation("IDLE_BACK", 12.f, 0, 2, 12, 2, 66, 100);
		this->animationComponent->addAnimation("WALK_BACK", 6.f, 0, 3, 9, 3, 66, 100);

		this->animationComponent->addAnimation("IDLE_LEFT", 12.f, 0, 4, 12, 4, 66, 100);
		this->animationComponent->addAnimation("WALK_LEFT", 6.f, 0, 5, 16, 5, 66, 100);

		this->animationComponent->addAnimation("IDLE_RIGHT", 12.f, 0, 6, 12, 6, 66, 100);
		this->animationComponent->addAnimation("WALK_RIGHT", 6.f, 0, 7, 16, 7, 66, 100);
	}

	if (state == "infight")
	{
		this->setPosition(x, y);

		this->createAnimationComponent(sprite_sheet);
		this->animationComponent->addAnimation("FIGHT_IDLE", 12.f, 0, 0, 0, 0, 329, 325);

	}
}

Player::~Player()
{

}

//accessors
const int Player::getStatsHP() const
{
	return this->hp;
}

const int Player::getStatsDefence() const
{
	return this->defence;
}

const int Player::getStatsBaseDMG() const
{
	return this->baseDmg;
}

const int Player::getStatsMaxDMG() const
{
	return this->maxDmg;
}

const int Player::getStatsMana() const
{
	return this->mana;
}

const int Player::getStatsExp() const
{
	return this->exp;
}

//functions

void Player::update(const float& dtime)
{
	this->movementComponent->update(dtime);
	//bool lastAnimation = false;

	if (this->movementComponent->getMoveState(MOVING))
	{
		//Down
		if (this->movementComponent->getMoveState(MOVINGDOWN))
		{
			//lastAnimation = this->movementComponent->getMoveState(MOVINGDOWN);

			this->animationComponent->play("WALK_FRONT", dtime);
		}
		//if (this->movementComponent->getMoveState(IDLE) && lastAnimation == this->movementComponent->getMoveState(MOVINGDOWN))
		//{
		//	this->animationComponent->play("IDLE_FRONT", dtime);
		//}

		//Up
		if (this->movementComponent->getMoveState(MOVINGUP))
		{
			this->animationComponent->play("WALK_BACK", dtime);
		}

		//Left
		if (this->movementComponent->getMoveState(MOVINGLEFT))
		{
			this->animationComponent->play("WALK_LEFT", dtime);
		}

		//Right
		if (this->movementComponent->getMoveState(MOVINGRIGHT))
		{
			this->animationComponent->play("WALK_RIGHT", dtime);
		}
	}
	else if (this->movementComponent->getMoveState(IDLE))
	{
		this->animationComponent->play("IDLE_FRONT", dtime);
	}

	if (!this->movementComponent)
	{
		this->animationComponent->play("FIGHT_IDLE", dtime);
	}

	this->hitboxComponent->update();
}
