#pragma once

#include "Game.h"

class GameObject
{
public:

	GameObject(const char* texturePath, int p_x, int p_y);
	~GameObject();

	void update();
	void render();


private:

	int x;
	int y;
	float scalingFactor;

	SDL_Texture* texture;
	SDL_Rect src, dest;
};
