#include "pch.h"
#include "Player.h"

//initializer functions
void Player::initializeVariables()
{
	//start stats
	this->hp = 200;
	this->mana = 0;
	this->defence = 2;
	this->baseDmg = 7;
	this->maxDmg = 9;
	this->exp = 0;

	this->idle = false;
}

// make switch cases instead of ifs!

void Player::initializeComponents()
{

}

Player::Player(float x, float y, sf::Texture& sprite_sheet, std::string state)
{
	this->initializeVariables();

		if(state =="ingame")
		{
			this->setPosition(x, y);

			this->createHitboxComponent(this->sprite, 0.f, 0.f, 66.f, 100.f); //15.f, 10.f, 35.f, 90.f
			this->createMovementComponent(140.f, 9.f, 4.f);
			this->createAnimationComponent(sprite_sheet);

			//animations
			this->animationComponent->addAnimation("IDLE_FRONT", 9.f, 0, 0, 13, 0, 66, 100);
			this->animationComponent->addAnimation("WALK_FRONT", 7.f, 0, 1, 9, 1, 66, 100);

			this->animationComponent->addAnimation("IDLE_BACK", 9.f, 0, 2, 12, 2, 66, 100);
			this->animationComponent->addAnimation("WALK_BACK", 7.f, 0, 3, 9, 3, 66, 100);

			this->animationComponent->addAnimation("IDLE_LEFT", 9.f, 0, 4, 12, 4, 66, 100);
			this->animationComponent->addAnimation("WALK_LEFT", 7.f, 0, 5, 16, 5, 66, 100);

			this->animationComponent->addAnimation("IDLE_RIGHT", 9.f, 0, 6, 12, 6, 66, 100);
			this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 0, 7, 16, 7, 66, 100);
		}
		else if(state == "infight")
		{
			this->setPosition(x, y);

			this->createAnimationComponent(sprite_sheet);
			this->animationComponent->addAnimation("FIGHT_IDLE", 12.f, 0, 0, 0, 0, 329, 325);
		}
}

Player::~Player()
{

}

//functions

void Player::loadStatsFromFile(const std::string file_name, int& Hp, int& Defence, int& BaseDmg, int& MaxDmg, int& Mana, int& Exp, int& Lvl, int& ifdead)
{
	std::ifstream in_file;
	in_file.open(file_name);

	if (in_file.is_open())
	{
		int hp = 0;
		int defence = 0;
		int baseDmg = 0;
		int maxDmg = 0;
		int mana = 0;
		int exp = 0;
		int lvl = 0;
		bool dead = false;

		in_file >> hp >> defence >> baseDmg >> maxDmg >> mana >> exp >> lvl >> dead;

		Hp = hp;
		Defence = defence;
		BaseDmg = baseDmg;
		MaxDmg = maxDmg;
		Mana = mana;
		Exp = exp;
		Lvl = lvl;
		ifdead = dead;
	}
	else
	{
		std::cout << "ERROR::PLAYER::COULDN'T LOAD STATS" << file_name << "\n";
	}

	in_file.close();
}

void Player::saveStatsToFile(const std::string file_name , int Hp, int Defence, int BaseDmg, int MaxDmg, int Mana, int Exp, int Lvl, int ifdead)
{
	std::ofstream out_file;
	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << Hp << " " << Defence << " " << BaseDmg << " " <<  MaxDmg << " " << Mana << " " << Exp << " " << Lvl << " " << ifdead;
	}
	else
	{
		std::cout << "ERROR::PLAYER::COULDN'T SAVE STATS" << file_name << "\n";
	}

	out_file.close();
}

void Player::update(const float& dtime)
{
	this->movementComponent->update(dtime);

	if (this->movementComponent->getMoveState(MOVING))
	{
		//Down
		if (this->movementComponent->getMoveState(MOVINGDOWN))
		{
			this->animationComponent->play("WALK_FRONT", dtime, this->movementComponent->getSpeed().y,this->movementComponent->getMaxSpeed());
		}

		//Up
		if (this->movementComponent->getMoveState(MOVINGUP))
		{
			this->animationComponent->play("WALK_BACK", dtime, this->movementComponent->getSpeed().y, this->movementComponent->getMaxSpeed());
		}

		//Left
		if (this->movementComponent->getMoveState(MOVINGLEFT))
		{
			this->animationComponent->play("WALK_LEFT", dtime, this->movementComponent->getSpeed().x, this->movementComponent->getMaxSpeed());
		}

		//Right
		if (this->movementComponent->getMoveState(MOVINGRIGHT))
		{
			this->animationComponent->play("WALK_RIGHT", dtime, this->movementComponent->getSpeed().x, this->movementComponent->getMaxSpeed());
		}
	}
	if (this->movementComponent->getMoveState(IDLE))
	{
		this->animationComponent->play("IDLE_FRONT", dtime);
	}

	if (!this->movementComponent)
	{
		this->animationComponent->play("FIGHT_IDLE", dtime);
	}

	this->hitboxComponent->update();
}
