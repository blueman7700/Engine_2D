#pragma once

#include "SDL.h"
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "../Exceptions/MissingComponentException.hpp"

#include <string>

class ColliderComponent : public Component
{
public:

	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="tag"></param>
	ColliderComponent(std::string tag)
	{
		this->tag = tag;

		width = 0;
		height = 0;
	}

	/// <summary>
	/// Create a new ColliderComponent with a set height and width.
	/// </summary>
	/// <param name="tag">Collider name.</param>
	/// <param name="w">Collider width.</param>
	/// <param name="h">Collider height.</param>
	ColliderComponent(std::string tag, int w, int h)
	{
		this->tag = tag;
		width = w;
		height = h;
	}

	/// <summary>
	/// Create a new collider component that matches the size of a given sprite.
	/// </summary>
	/// <param name="tag">Collider name.</param>
	/// <param name="sprite">Sprite component to match size to.</param>
	ColliderComponent(std::string tag, SpriteComponent& sprite)
	{
		this->tag = tag;
		width = sprite.outW;
		height = sprite.outH;
	}

	void init() override 
	{
		if (!ownerEntity->hasComponent<TransformComponent>())
		{
			throw new MissingComponentException(typeid(TransformComponent).name());
		}

		transform = &ownerEntity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void update() override
	{
		collider.x = transform->pos.x;
		collider.y = transform->pos.y;

		collider.w = width;
		collider.h = height;
	}

	void setColliderSize(int w, int h)
	{
		width = w;
		height = h;
	}

	void setColliderSize(SpriteComponent& sprite)
	{
		width = sprite.outH;
		height = sprite.outH;
	}

private:

	int width, height;
};