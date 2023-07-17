#include "AssetManager.hpp"

AssetManager::AssetManager(Manager* man)
{
	AssetManager::manager = man;
}

AssetManager::~AssetManager()
{}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}