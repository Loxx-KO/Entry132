#pragma once

enum TILE_TYPES
{
	DEAFULT = 0,
	DAMAGING
};

class Tile
{
private:

protected:
	sf::RectangleShape tile;
	//type - different types of tiles (slowing ones, colliding etc)
	short tile_type;
	bool collision;

public:
	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizef, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision, short tile_type);
	virtual ~Tile();

	//accessors
	const std::string getAString() const;

	//functions
	void update();
	void render(sf::RenderTarget& target);
};

