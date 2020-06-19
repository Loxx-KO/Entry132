#include "pch.h"
#include "AnimationComponent.h"

//animation comtonent class

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& sprite_sheet)
	:sprite(sprite), spriteSheet(sprite_sheet), lastAnimation(NULL), priorityAnimation(NULL)
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

void AnimationComponent::play(const std::string key, const float& dtime, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			if (this->animations[key]->play(dtime))		//if priority animetion is done - remove it
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		//check if there is any priority
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dtime);
	}
}

void AnimationComponent::play(const std::string key, const float& dtime, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			if(this->animations[key]->play(dtime, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dtime, abs(modifier / modifier_max));
	}
}

//animation class inside it

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

bool AnimationComponent::Animation::play(const float& dtime)
{
	//update timer

	bool done = false;
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
			done = true;
		}
		this->sprite.setTextureRect(this->currentFrame);
	}
	return done;
}

bool AnimationComponent::Animation::play(const float& dtime, float mod_procent)
{
	//update timer
	if (mod_procent < 0.6f)
	{
		mod_procent = 0.6f;
	}

	this->timer += mod_procent * 110.f * dtime;
	bool done = false;

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
			done = true;
		}
		this->sprite.setTextureRect(this->currentFrame);
	}
	return done;
}

void AnimationComponent::Animation::reset()
{
	this->timer = this->frameSpeed;
	this->currentFrame = this->firstFrame;
}
