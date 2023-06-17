#pragma once

#include "../Game.h"
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "AnimationComponent.hpp"

class KeyboardController : public Component
{
public:

	TransformComponent* transform;
	AnimationComponent* anim;

	void init() override
	{
		transform = &ownerEntity->getComponent<TransformComponent>();
		anim = &ownerEntity->getComponent<AnimationComponent>();
	}

	void update() override
	{

		// Regarding the weird ternary, they are there to deal
		// with the edge case when a user presses two conflicting
		// direction keys at the same time. E.g. when a user holds down the
		// 'a' and 'd' keys, the entity will stop. The entity will then
		// continue in the opposite direction of whatever key is let go first. 

		// In short, fuck end-users.

		// on another note, the animations are a bit fucked, cba to deal with it now.

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{

			case SDLK_w:
				u = true;
				transform->velocity.y = d ? 0 : -1;
				if (anim != nullptr)
				{
					anim->setAnimation("WALK_UP");
				}
				break;
			case SDLK_s:
				d = true;
				transform->velocity.y = u ? 0 : 1;
				if (anim != nullptr)
				{
					anim->setAnimation("WALK_DOWN");
				}
				break;
			case SDLK_a:
				l = true;
				transform->velocity.x = r ? 0 : -1;
				if (anim != nullptr)
				{
					anim->setAnimation("WALK_LEFT");
				}
				break;
			case SDLK_d:
				r = true;
				transform->velocity.x = l ? 0 : 1;
				if (anim != nullptr)
				{
					anim->setAnimation("WALK_RIGHT");
				}
				break;
			case SDLK_LSHIFT:
				sprint = true;
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{

			case SDLK_w:
				u = false;
				transform->velocity.y = d ? 1 : 0;
				break;
			case SDLK_s:
				d = false;
				transform->velocity.y = u ? -1 : 0;
				break;
			case SDLK_a:
				l = false;
				transform->velocity.x = r ? 1 : 0;
				break;
			case SDLK_d:
				r = false;
				transform->velocity.x = l ? -1 : 0;
				break;
			case SDLK_LSHIFT:
				sprint = false;
				break;

			default:
				break;
			}

			if (anim != nullptr 
				&& transform->velocity.x == 0 
				&& transform->velocity.y == 0)
			{
				anim->setAnimation("IDLE");
			}
		}
	}

private:

	bool u = false, d = false, l = false, r = false;
	bool sprint = false;

};