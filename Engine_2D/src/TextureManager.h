#pragma once

#include "Game.h"
#include "Logger.h"

#include <string>

class TextureManager
{

public:
	static SDL_Texture* loadTexture(const char* filename);
	static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};
