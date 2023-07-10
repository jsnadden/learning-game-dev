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

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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
				Map::LoadMap("assets/16x16_island.map", 16, 16);
				
				player.addComponent<TransformComponent>(2);
				player.addComponent<SpriteComponent>("assets/peach.png");
				player.addComponent<KeyboardController>();
				player.addComponent <ColliderComponent>("player");
				player.addGroup(groupPlayers);

				wall.addComponent<TransformComponent>(400.0f, 320.0f, 32, 32, 1);
				wall.addComponent<SpriteComponent>("assets/dirt.png");
				wall.addComponent<ColliderComponent>("wall");
				wall.addGroup(groupMap);
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

	for (auto& cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}

}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}