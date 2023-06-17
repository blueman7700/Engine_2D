#include "TileMap.h"
#include "Game.h"
#include "Logger.h"

#include <fstream>

TileMap::TileMap()
{

}

TileMap::~TileMap()
{

}

// should be able to load maps of arbitrary size.
void TileMap::loadMap(std::string path, int sizeX, int sizeY)
{
	char currTile;
	std::fstream fileStream;
	fileStream.open(path);

	// TODO: handle multiple map layers
	try
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
			{
				fileStream.get(currTile);
				Game::addTileToMap(atoi(&currTile), x*32, y*32);
				fileStream.ignore();
			}
		}
	}
	catch (const std::exception& e)
	{
		Logger::logException(e);
	}

	fileStream.close();
}
