#pragma once

#include "ECS.hpp"
#include "../Vector2D.h"

struct TransformComponent : public Component
{
public:

	Vector2D pos;
	Vector2D velocity;

	float rotation = 0;

	int speedMultiplier = 1;

	TransformComponent()
	{
		pos.zero();
		velocity.zero();
	}

	TransformComponent(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		velocity.zero();
	}

	TransformComponent(float x, float y, float multiplier)
	{
		pos.x = x;
		pos.y = y;
		speedMultiplier = multiplier;
		velocity.zero();
	}

	TransformComponent(float multiplier)
	{
		pos.zero();
		velocity.zero();
		speedMultiplier = multiplier;
	}

	void update() override
	{
		pos.x += velocity.x * speedMultiplier;
		pos.y += velocity.y * speedMultiplier;
	}

};