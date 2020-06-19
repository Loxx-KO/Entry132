#include "pch.h"
#include "TileMap.h"

void TileMap::clearMemory()
{
	for (size_t x = 0; x < maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete[] map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			delete[] map[x][y];
		}
		delete[] map[x];
	}
	delete[] map;

}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->texture_file = texture_file;

	//initializing map

	map = new Tile *** [this->maxSize.x];
	for (size_t x = 0; x < maxSize.x; x++)
	{
		map[x] = new Tile**[this->maxSize.y];

		for (size_t y = 0; y < maxSize.y; y++)
		{
			map[x][y] = new Tile* [this->layers];

			for (size_t z = 0; z < layers; z++)
			{
				map[x][y][z] = nullptr;
			}
		}
	}

	if(!this->tileTextureSheet.loadFromFile(texture_file))
	{
		std::cout << "ERROR::TILEMAP::COULDN'T LOAD TILETEXTURE\n";
	}
}

TileMap::~TileMap()
{
	this->clearMemory();
}

//accessors
const sf::Texture* TileMap::getTileTextureSheet() const
{
	return &this->tileTextureSheet;
}

//functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	// takes three indexes x,y,z from the mouse position at adds a tile in that position (if it fits into the array)
	//error check
	if (x < this->maxSize.x && y < this->maxSize.y && x >= 0 && y >= 0 
		&& z < this->layers && z >= 0)
	{
		//checks if you can add a tile - if tile is already placed there you can't place another one on top of it
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTextureSheet, texture_rect, collision, type);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	// takes three indexes x,y,z from the mouse position at removes a tile in that position (if it fits into the array)
	if (x < this->maxSize.x && y < this->maxSize.y && x >= 0 && y >= 0
		&& z < this->layers && z >= 0)
	{
		//checks if you can remove a tile - if tile is already placed there you can't place another one on top of it
		if (this->map[x][y][z] != nullptr)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/*saved tile map to the text file	
	To save: size x,y | gridSize 
	All tiles: gridPos x y layers(z) | textureRect x y | texture file | collision | type
	*/

	std::ofstream out_file;
	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->texture_file << "\n";

		for (size_t x = 0; x < maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++)
			{
				for (size_t z = 0; z < layers; z++)
				{
					if(this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAString() << " ";
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::WRONG FILE NAME TO SAVE THE TILEMAP!" << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	/*saved tile map to the text file
	To save: size x,y | gridSize
	All tiles: gridPos x y layers(z) | textureRect x y | texture file | collision | type
	*/

	std::ifstream in_file;
	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned texture_rectX = 0;
		unsigned texture_rectY = 0;
		bool collision = false;
		short type = 0;

		//loading size
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->texture_file = texture_file;

		this->clearMemory();

		//loading tiles
		map = new Tile * **[this->maxSize.x];
		for (size_t x = 0; x < maxSize.x; x++)
		{
			map[x] = new Tile * *[this->maxSize.y];

			for (size_t y = 0; y < maxSize.y; y++)
			{
				map[x][y] = new Tile * [this->layers];

				for (size_t z = 0; z < this->layers; z++)
				{
					map[x][y][z] = nullptr;
				}
			}
		}

		//load all tiles
		while (in_file >> x >> y >> z >> texture_rectX >> texture_rectY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTextureSheet, sf::IntRect(texture_rectX, texture_rectY, this->gridSizeU, this->gridSizeU) ,collision, type);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::WRONG FILE NAME TO LOAD THE TILEMAP!" << file_name << "\n";
	}


	in_file.close();
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (size_t x = 0; x < maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				if (map[x][y][z] != nullptr)
					map[x][y][z]->render(target);
			}
		}
	}
}
