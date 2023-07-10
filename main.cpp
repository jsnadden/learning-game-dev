#include "SDL.h"
#include "Game.hpp"
#include <stdint.h>
#include "Vector2D.hpp"

Game* game = nullptr;
int WINDOW_WIDTH = 512;
int WINDOW_HEIGHT = 512;

int main(int argc, char* argv[])
{
	const int FPS = 60; // Max frame rate
	const int frameDelay = 1000 / FPS;
	uint32_t frameStart;
	int frameTime;

	game = new Game();
	game->init("A window title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

	// Game loop
	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		// Perform frame limiting
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) { SDL_Delay(frameDelay - frameTime); }
	}

	game->clean();

	return 0;
}