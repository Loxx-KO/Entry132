#pragma once

class AnimationComponent
{
private:
	class Animation 
	{
	public:
		//variables
		sf::Sprite& sprite;
		sf::Texture& spriteSheet;

		sf::IntRect firstFrame;
		sf::IntRect currentFrame;
		sf::IntRect lastFrame;

		float timer;
		float frameSpeed;

		int width;
		int height;

		Animation(sf::Sprite& sprite, sf::Texture& sprite_sheet, float frameSpeed,
			int first_frame_x, int first_frame_y, int frames_x, int frames_y, int width, int height);
		virtual ~Animation();

		//functions
		bool play(const float& dtime);
		bool play(const float& dtime, float mod_procent);
		//void pause();
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& spriteSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:

	AnimationComponent(sf::Sprite& sprite, sf::Texture& sprite_sheet); //forcing sprite and texturesheet
	virtual ~AnimationComponent();
	//accessors

	//functions
	void addAnimation(const std::string key, float frame_Speed,
		int first_frame_x, int first_frame_y, int frames_x, int frames_y, int width, int height);
	void play(const std::string key, const float& dtime, const bool priority = false);
	void play(const std::string key, const float& dtime, const float& modifier, const float& modifier_max, const bool priority = false);
};

