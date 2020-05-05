#include "pch.h"
#include "Enemy.h"

void Enemy::initializeVariables()
{

}

Enemy::Enemy(float x, float y, sf::Texture& texture, std::string name)
{
	this->initializeVariables();

	if (name == "testenemy")
	{
		this->createHitboxComponent(this->sprite, 0.f, 0.f, 70.f, 100.f);
		this->createMovementComponent(0.f, 0.f, 0.f);

		this->setTexture(texture);
		this->setPosition(x, y);

		this->name = "testenemy";
		this->hp = 30;
		this->baseDmg = 3;
		this->maxDmg = 5;
		this->exp = 15;
	}

	if (name == "blob")
	{
		this->createHitboxComponent(this->sprite, 0.f, 0.f, 70.f, 100.f);
		this->createMovementComponent(0.f, 0.f, 0.f);

		this->setTexture(texture);
		this->setPosition(x, y);

		this->name = "blob";
		this->hp = 20;
		this->baseDmg = 2;
		this->maxDmg = 4;
		this->exp = 8;
	}

	if (name == "snake")
	{
		this->createHitboxComponent(this->sprite, 0.f, 0.f, 70.f, 100.f);
		this->createMovementComponent(0.f, 0.f, 0.f);

		this->setTexture(texture);
		this->setPosition(x, y);

		this->name = "snake";
		this->hp = 40;
		this->baseDmg = 5;
		this->maxDmg = 8;
		this->exp = 25;
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
