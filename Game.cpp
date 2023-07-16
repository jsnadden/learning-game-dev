#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

//Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, 800, 640 };

// TODO (refactor) scrap this vector and just use colliderGroup
std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());

enum groupLabels : std::size_t
{
	mapGroup,
	playerGroup,
	enemyGroup,
	colliderGroup
};

auto& tiles(manager.getGroup(mapGroup));
auto& players(manager.getGroup(playerGroup));
auto& enemies(manager.getGroup(enemyGroup));
//auto& colliders(manager.getGroup(colliderGroup));

const char* terrainTiles = "assets/terrain.png";

bool Game::isRunning = false;

Game::Game()
{
	counter = 0;
}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	// Initialize SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		isRunning = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			isRunning = false;
		}
		else
		{
			// Create renderer
			Game::renderer = SDL_CreateRenderer(window, -1, 0);
			if (Game::renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				isRunning = false;
			}
			else
			{
				// Set background colour to white
				SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);

				isRunning = true;

				//map = new Map();
				Map::LoadMap("assets/map0.map", 16, 16);
				
				player.addComponent<TransformComponent>(4);
				player.addComponent<SpriteComponent>("assets/ship.png", true);
				player.addComponent<KeyboardController>();
				player.addComponent <ColliderComponent>("player");
				player.addGroup(playerGroup);


			}
		}
	}
}

void Game::handleEvents()
{
	

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	// TODO: the following will break if our map is a different size, shape, or scale!
	//		 We need some variables to keep track of the current map bounds
	camera.x = player.getComponent<TransformComponent>().position.x - 400 + 64;
	camera.y = player.getComponent<TransformComponent>().position.y - 320 + 64;
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x + camera.w > 1024) camera.x = 1024 - camera.w;
	if (camera.y + camera.h > 1024) camera.y = 1024 - camera.h;

	/*
	// Check for binary collisions:
	for (auto& cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
	*/

}

void Game::render()
{
	SDL_RenderClear(Game::renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	// Send to display
	SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
	// Clean up SDL resources
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, terrainTiles);
	tile.addGroup(mapGroup);
}