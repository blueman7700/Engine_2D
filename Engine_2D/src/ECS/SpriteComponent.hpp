#pragma once

#include "TransformComponent.hpp"
#include "../TextureManager.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:

	int outW, outH;

	SpriteComponent() = default;

	/// <summary>
	/// Sprite Component constructor.
	/// </summary>
	/// <param name="path">Path to texture</param>
	SpriteComponent(const char* path)
	{
		setTexture(path);
		
		// Default source sprite position is 0, 0.
		srcRect.x = srcRect.y = 0;

		// Default source sprite size is 32x32px.
		srcRect.w = srcRect.h = 32;

		baseOutH = srcRect.h;
		baseOutW = srcRect.w;
	}

	/// <summary>
	/// Sprite Component constructor.
	/// </summary>
	/// <param name="path">Path to texture</param>
	/// <param name="x">Source texture X coordinate.</param>
	/// <param name="y">Source texture Y coordinate.</param>
	/// <param name="w">Source texture width.</param>
	/// <param name="h">Source texture height.</param>
	SpriteComponent(const char* path, int x, int y, int w, int h)
	{
		setTexture(path);
		srcRect.x = x;
		srcRect.y = y;
		srcRect.h = h;
		srcRect.w = w;

		baseOutH = srcRect.h;
		baseOutW = srcRect.w;
	}

	/// <summary>
	/// Sprite Component constructor.
	/// </summary>
	/// <param name="path">Path to texture</param>
	/// <param name="x">Source texture X coordinate.</param>
	/// <param name="y">Source texture Y coordinate.</param>
	/// <param name="w">Source texture width.</param>
	/// <param name="h">Source texture height.</param>
	/// <param name="scale">Amount to scale the source sprite by.</param>
	SpriteComponent(const char* path, int x, int y, int w, int h, float scale)
	{
		setTexture(path);
		srcRect.x = x;
		srcRect.y = y;
		srcRect.h = h;
		srcRect.w = w;
		spriteScale = scale;

		baseOutH = srcRect.h;
		baseOutW = srcRect.w;
	}

	/// <summary>
	/// Sprite Component constructor.
	/// </summary>
	/// <param name="path">Path to texture</param>
	/// <param name="x">Source texture X coordinate.</param>
	/// <param name="y">Source texture Y coordinate.</param>
	/// <param name="w">Source texture width.</param>
	/// <param name="h">Source texture height.</param>
	/// <param name="outW">Output width.</param>
	/// <param name="outH">Output height.</param>
	SpriteComponent(const char* path, int x, int y, int w, int h, int outW, int outH)
	{
		setTexture(path);
		srcRect.x = x;
		srcRect.y = y;
		srcRect.h = h;
		srcRect.w = w;

		baseOutH = outH;
		baseOutW = outW;
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(tex);
	}

	void init() override 
	{
		transform = &ownerEntity->getComponent<TransformComponent>();
		outH = baseOutH * spriteScale;
		outW = baseOutW * spriteScale;
	}

	void update() override
	{
		// Set sprite destination to transform component position
		destRect.x = static_cast<int>(transform->pos.x);
		destRect.y = static_cast<int>(transform->pos.y);

		outH = baseOutH * spriteScale;
		outW = baseOutW * spriteScale;

		destRect.h = outH;
		destRect.w = outW;
	}

	void draw() override
	{
		TextureManager::draw(tex, srcRect, destRect);
	}

	void setTexture(const char* path)
	{
		tex = TextureManager::loadTexture(path);
	}

	void setScale(float scale)
	{
		spriteScale = scale;
	}

	void setSourceRect(int x, int y, int w, int h)
	{
		srcRect.x = x;
		srcRect.y = y;
		srcRect.w = w;
		srcRect.h = h;
	}

protected:
	TransformComponent* transform;
	SDL_Texture* tex;
	SDL_Rect srcRect, destRect;
	float spriteScale = 1;
	int baseOutW, baseOutH;
};