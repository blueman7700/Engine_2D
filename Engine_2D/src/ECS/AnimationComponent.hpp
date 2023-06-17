#pragma once

#include "SpriteComponent.hpp"
#include "Animation.hpp"

#include <map>

class AnimationComponent : public SpriteComponent
{
public:

	AnimationComponent() = default;
	AnimationComponent(const char* path)
	{
		setTexture(path);
		// Default source sprite position is 0, 0.
		srcRect.x = srcRect.y = 0;

		// Default source sprite size is 64x64px.
		srcRect.w = srcRect.h = 64;

		baseOutH = srcRect.h;
		baseOutW = srcRect.w;
	}

	AnimationComponent(const char* path, int size)
	{
		setTexture(path);

		// Default source sprite position is 0, 0.
		srcRect.x = srcRect.y = 0;

		srcRect.w = srcRect.h = size;

		baseOutH = srcRect.h;
		baseOutW = srcRect.w;

		spriteScale = 4;
	}

	AnimationComponent(const char* path, int size, float outScale)
	{
		setTexture(path);

		// Default source sprite position is 0, 0.
		srcRect.x = srcRect.y = 0;

		srcRect.w = srcRect.h = size;

		baseOutH = srcRect.h;
		baseOutW = srcRect.w;

		spriteScale = outScale;
	}

	~AnimationComponent()
	{
		SDL_DestroyTexture(tex);
	}

	/// <summary>
	/// Update the sprite position, size, frame, etc.
	/// </summary>
	void update() override
	{
		if (animRunning)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks64() / liveAnimation.frameMills) % liveAnimation.frames);
			srcRect.y = srcRect.h * liveAnimation.animIndex;
		}

		// Set sprite destination to transform component position
		destRect.x = static_cast<int>(transform->pos.x);
		destRect.y = static_cast<int>(transform->pos.y);

		outH = baseOutH * spriteScale;
		outW = baseOutW * spriteScale;

		destRect.h = outW;
		destRect.w = outH;
	}

	/// <summary>
	/// Draw the set frame to the texture buffer.
	/// </summary>
	void draw() override
	{
		TextureManager::draw(tex, srcRect, destRect);
	}

	/// <summary>
	/// Add a new animation to the animation map.
	/// </summary>
	/// <param name="a">New animation data.</param>
	/// <param name="name">Name of the animation.</param>
	void addAnimation(Animation a, const char* name) 
	{
		animations.emplace(name, a);
	};

	/// <summary>
	/// Change what animation should be played.
	/// </summary>
	/// <param name="animName">Name of the animation to play.</param>
	void setAnimation(const char* animName)
	{
		// todo: change current animation.
		liveAnimation = animations[animName];
	}

	/// <summary>
	/// Start playing the current animation.
	/// </summary>
	void start() { animRunning = true; }

	/// <summary>
	/// Stop playing the current animation.
	/// </summary>
	void stop() { animRunning = false; }

private:
	bool animRunning = false;
	Animation liveAnimation;
	std::map<const char*, Animation> animations;
};