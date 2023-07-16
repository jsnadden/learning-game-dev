#pragma once

#include <iostream>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.hpp"
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();

	void clean();

	static void AddTile(int srcX, int srcY, int xPos, int yPos);

	static bool isRunning;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static std::vector<ColliderComponent*> colliders;

private:
	
	SDL_Window* window;
	int counter;
};