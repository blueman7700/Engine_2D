#include "GameObject.h"
#include "TextureManager.h"
#include "Logger.h"

GameObject::GameObject(const char* texturePath, int p_x, int p_y)
	: x(p_x), y(p_y)
{
	// load object textures
	texture = TextureManager::loadTexture(texturePath);

	src.h = 64;
	src.w = 32;
	src.x = 0;
	src.y = 0;

	scalingFactor = 2.0f;

	dest.x = x;
	dest.y = y;
	dest.w = (int) ((float) src.w * scalingFactor);
	dest.h = (int) ((float) src.h * scalingFactor);
}

GameObject::~GameObject()
{
	Game::renderer = nullptr;
	SDL_DestroyTexture(texture);
	texture = nullptr;
	Logger::log(INFO, "GameObj", "GameObject Destroyed Successfully!");
}

void GameObject::update()
{
	x++;
	y++;

	dest.x = x;
	dest.y = y;
	dest.w = src.w * scalingFactor;
	dest.h = src.h * scalingFactor;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}