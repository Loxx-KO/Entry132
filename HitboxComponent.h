#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::RectangleShape hitboxEnemy;
	float offsetx;
	float offsety;

	sf::FloatRect nextPosition;

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

	void update();
	void render(sf::RenderTarget& target);
};

