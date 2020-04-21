#include "pch.h"
#include "AnimationComponent.h"

//animation comtonent class

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& sprite_sheet)
	:sprite(sprite), spriteSheet(sprite_sheet)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key, float frame_Speed,
	int first_frame_x, int first_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->spriteSheet, frame_Speed,
		first_frame_x, first_frame_y, frames_x, frames_y, width, height);
}

void AnimationComponent::play(const std::string key, const float& dtime)
{
	this->animations[key]->play(dtime);
}


//animation class insite it


AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& sprite_sheet, float frame_Speed,
	int first_frame_x, int first_frame_y, int frames_x, int frames_y, int width, int height)
	:sprite(sprite), spriteSheet(sprite_sheet), frameSpeed(frame_Speed), width(width), height(height), timer(timer)
{
	this->timer = 0.f;
	this->firstFrame = sf::IntRect(first_frame_x * width , first_frame_y * height, width, height);
	this->currentFrame = this->firstFrame;
	this->lastFrame = sf::IntRect(frames_x * width , frames_y * height, width, height);

	this->sprite.setTexture(this->spriteSheet, true);
	this->sprite.setTextureRect(this->firstFrame);
}

AnimationComponent::Animation::~Animation()
{

}

void AnimationComponent::Animation::play(const float& dtime)
{
	//update timer
	this->timer += 110.f * dtime;
	if (this->timer >= this->frameSpeed)
	{
		//reset timer
		this->timer = 0.f;

		//animation
		if (this->currentFrame != this->lastFrame)
		{
			this->currentFrame.left += this->width;
		}
		else //reset
		{
			this->currentFrame.left = this->firstFrame.left;
		}

		this->sprite.setTextureRect(this->currentFrame);
	}
}

void AnimationComponent::Animation::reset()
{
	this->timer = 0.f;
	this->currentFrame = this->firstFrame;
}
