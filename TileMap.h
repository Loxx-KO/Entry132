#pragma once
#include "pch.h"
#include "Tile.h"
#include "Entity.h"
#include "HitboxComponent.h"

class TileMap
{
private:
	sf::Vector2u mapSize;
	std::vector < std::vector < std::vector < Tile > > > map;  // x , y than tile

public:
	TileMap();
	virtual ~TileMap();

	//accessors
	//functions
};