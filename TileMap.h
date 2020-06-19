#pragma once
#include "pch.h"
#include "Tile.h"
#include "Entity.h"
#include "HitboxComponent.h"

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::string texture_file;

	// Tile**** -> first we need to have Tile* (pointer to Tile class) and after that *** for each dimension
	Tile**** map;
	sf::Texture tileTextureSheet;

	void clearMemory();

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	//accessors
	const sf::Texture* getTileTextureSheet() const;

	//functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget &target);
};