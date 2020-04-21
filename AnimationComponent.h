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
		void play(const float& dtime);
		void pause();
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& spriteSheet;
	std::map<std::string, Animation*> animations;

public:

	AnimationComponent(sf::Sprite& sprite, sf::Texture& sprite_sheet); //forcing sprite and texturesheet
	virtual ~AnimationComponent();

	//functions
	void addAnimation(const std::string key, float frame_Speed,
		int first_frame_x, int first_frame_y, int frames_x, int frames_y, int width, int height);
	void play(const std::string key, const float& dtime);
};

