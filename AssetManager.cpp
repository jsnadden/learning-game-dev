#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager* man)
{
	AssetManager::manager = man;
}

AssetManager::~AssetManager()
{}

void AssetManager::CreateProjectile(Vector2D position, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(position.x, position.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>("projectile_test", false);
	projectile.addComponent<ProjectileComponent>(range, speed);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::projectileGroup);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}