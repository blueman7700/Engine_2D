#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "SDL.h"

enum TileType
{
	WATER = 0,
	DIRT = 1,
	STONE = 2,
	GRASS = 3,
	INVISIBLE = 4
};

class TileComponent : public SpriteComponent
{
public:

	TileType type;
	std::string path;

	TileComponent() = default;
	TileComponent(int type)
	{
		this->type = (TileType)type;
		int x = 0, y = 0;

		switch (this->type)
		{
		case GRASS:
			path = "assets/grass.png";
			break;
		case STONE:
			path = "assets/stone.png";
			break;
		case DIRT:
			path = "assets/dirt.png";
			break;
		case WATER:
			path = "assets/water.png";
			break;
		default:
			break;
		}

		setTexture(path.c_str());

		srcRect.x = x;
		srcRect.y = y;

		// all tiles should be 32x32px textures.
		srcRect.w = 32;
		srcRect.h = 32;
		this->baseOutW = 32;
		this->baseOutH = 32;

		spriteScale = 1;
	}
};