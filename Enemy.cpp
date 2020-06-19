#include "pch.h"
#include "Enemy.h"

void Enemy::initializeVariables()
{
	this->name = "";
	this->hp = 0;
	this->baseDmg = 0;
	this->maxDmg = 0;
	this->exp = 0;
}

Enemy::Enemy(float x, float y, sf::Texture& texture, std::string name, const short unsigned STATE)
{
	this->initializeVariables();

	switch (STATE)
	{
	case INGAME:
	{
		if (name == "testenemy")
		{
			this->setPosition(x, y);
			this->createHitboxComponent(this->sprite, 0.f, 0.f, 70.f, 100.f);
			this->createMovementComponent(0.f, 0.f, 0.f);

			this->setTexture(texture);
		}

		if (name == "blob")
		{
			this->setPosition(x, y);
			this->createHitboxComponent(this->sprite, 0.f, 0.f, 70.f, 100.f);
			this->createMovementComponent(0.f, 0.f, 0.f);

			this->setTexture(texture);
		}

		if (name == "snake")
		{
			this->setPosition(x, y);
			this->createHitboxComponent(this->sprite, 0.f, 0.f, 70.f, 100.f);
			this->createMovementComponent(0.f, 0.f, 0.f);

			this->setTexture(texture);
		}
	}
	case INFIGHT:
	{
		if (name == "testenemy")
		{
			this->setTexture(texture);
			this->setPosition(x, y);

			this->name = "testenemy";
			this->hp = 30;
			this->baseDmg = 2;
			this->maxDmg = 4;
			this->exp = 15;
		}

		if (name == "blob")
		{
			this->setTexture(texture);
			this->setPosition(x, y);

			this->name = "blob";
			this->hp = 20;
			this->baseDmg = 1;
			this->maxDmg = 3;
			this->exp = 10;
		}

		if (name == "snake")
		{
			this->setTexture(texture);
			this->setPosition(x, y);

			this->name = "snake";
			this->hp = 40;
			this->baseDmg = 90;
			this->maxDmg = 100;
			this->exp = 40;
		}
	}

	default:
		break;
	}
}

Enemy::~Enemy()
{

}

//accessors
const sf::FloatRect Enemy::CreateEnemyBox() const
{
	return this->getGlobalBounds();
}

const int Enemy::getEnemyHP() const
{
	return this->hp;
}

const int Enemy::getEnemyBaseDMG() const
{
	return this->baseDmg;
}

const int Enemy::getEnemyMaxDMG() const
{
	return this->maxDmg;
}

const int Enemy::getEnemyExp() const
{
	return this->exp;
}

const std::string Enemy::getName() const
{
	return this->name;
}

//functions
void Enemy::update(const float& dtime)
{
	this->movementComponent->update(dtime);
	this->hitboxComponent->update();
}