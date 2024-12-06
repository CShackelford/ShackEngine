#include "Map.h"
#include "Game.hpp"
#include <fstream>
#include <string>
#include "ECS\ECS.h"
#include "ECS\Components.h"

extern Manager manager;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts) {
	scaledSize = ms * ts;
}

Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);
	int srcX, srcY;
	int count = 0;


	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
//			std::string tileID;
			// Number of Columns in tileset: 2048
			std::string num_as_string = "";

			for (int i = 0; i < 4; i++) {
				mapFile.get(c);
				num_as_string += c;
			}
			count += 1;
			srcY = stoi(num_as_string) / 65;
			srcX = stoi(num_as_string) % 65;
			AddTile(srcX * 32, srcY * 32, x * (scaledSize), y * (scaledSize));

			//below prints some sort of loading screen so I can see how many tiles are left to be parsed.
			std::cout << count << "/" << sizeY * sizeX << std::endl;

			mapFile.ignore();

		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}
