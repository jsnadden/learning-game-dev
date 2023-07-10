#pragma once
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int xIn, int yIn, int widthIn, int heightIn, int idIn)
	{
		tileRect.x = xIn;
		tileRect.y = yIn;
		tileRect.w = widthIn;
		tileRect.h = heightIn;

		tileID = idIn;

		switch (tileID)
		{
		case 0:
			path = "assets/water.png";
			break;
		case 1:
			path = "assets/dirt.png";
			break;
		case 2:
			path = "assets/grass.png";
			break;
		default:
			break;
		}


	}

	void init() override
	{
		entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
		
	}


};
