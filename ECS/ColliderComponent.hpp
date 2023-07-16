#pragma once
#include <string>
#include "SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string tagIn)
	{
		tag = tagIn;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		
		Game::colliders.push_back(this);
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x) - Game::camera.x;
		collider.y = static_cast<int>(transform->position.y) - Game::camera.y;
		collider.w = (transform->width) * (transform->scale);
		collider.h = (transform->height) * (transform->scale);
	}


};