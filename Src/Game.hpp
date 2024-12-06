#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "AssetManager.h"

class ColliderComponent;

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	void loading();

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;
//	static AssetManager *assets;
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders
	};

private:
	int cnt =0;
	bool isRunning;
	SDL_Window *window;
};


#endif