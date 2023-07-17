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

	static bool isRunning;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;

	static int windowWidth;
	static int windowHeight;

	static enum groupLabels : std::size_t
	{
		mapGroup,
		playerGroup,
		enemyGroup,
		colliderGroup
	};

private:
	
	SDL_Window* window;
	int counter;
};