#pragma once
#include "ECS.hpp"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, const char* path)
	{
		texture = TextureManager::loadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = destRect.h = 64;

		position.x = xPos;
		position.y = yPos;
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		/* TODO: only draw tiles which are currently visible/on screen.
				 I'll research how this is typically done, but I guess adding
				 a "bool active" flag would be fine */ 
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}


};
