#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetx;
	float offsety;

	sf::FloatRect box;

public:
	HitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	//accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//functions
	bool collision(sf::FloatRect box);
	void update();
	void render(sf::RenderTarget& target);
};

