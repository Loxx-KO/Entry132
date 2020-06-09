#include "pch.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->tile_type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizef, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision, short tile_type)
{
	this->tile.setSize(sf::Vector2f(gridSizef, gridSizef)); 
	this->tile.setPosition(sf::Vector2f(static_cast<float>(grid_x) * gridSizef, static_cast<float>(grid_y) * gridSizef));
	this->tile.setTexture(&texture);
	this->tile.setTextureRect(texture_rect);

	this->collision = collision;
	this->tile_type = tile_type;
}

Tile::~Tile()
{
}

//accessors
const std::string Tile::getAString() const
{
	std::stringstream stream;

	stream << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " " << this->collision << " " << this->tile_type;

	return stream.str();
}

//functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tile);
}
