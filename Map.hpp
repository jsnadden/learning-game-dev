#pragma once
#include <string>

class Map
{
public:

	Map(const char* mfp, int ts, int ms);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xPos, int yPos);
	
private:

	const char* mapFilePath;
	int tileSize;
	int mapScale;
	int scaledSize;

};

