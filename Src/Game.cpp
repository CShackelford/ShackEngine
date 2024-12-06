#include "Game.hpp"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,768,768 };

//AssetManager* Game::assets = new AssetManager(&manager);

auto& player(manager.addEntity());



//auto& collisions(manager.getGroup(groupColliders));

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	else {
		isRunning = false;
	}

//	assets->AddTexture("terrain", "assets/cursed_lands_tileset.png");
//	assets->AddTexture("player", "assets/adjusted_idle.png");



	map = new Map("assets/cursed_lands_tileset.png", 1, 32);
	map->LoadMap("assets/front-of-dark-keep.csv", 20, 20);

	player.addComponent<TransformComponent>(10, 10, 34, 96, 2);
	player.addComponent<SpriteComponent>("assets/adjusted_idle.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 320;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;


	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}
}

void Game::loading() {
	// Loading screen logic
	SDL_Color color = { 255, 255, 255, 255 }; // White
	SDL_Rect loadingBarRect = { 200, 300, 100, 20 };

	for (int i = 0; i <= 100; ++i) {
		// Simulate loading progress
		SDL_Delay(5000); // Adjust delay for desired loading speed

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw loading bar
		loadingBarRect.w = i * 3;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
		SDL_RenderFillRect(renderer, &loadingBarRect);

		// Render text
//		SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Loading...", color);
//		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//		SDL_Rect textRect = { 300, 250, textSurface->w, textSurface->h };
//		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
//		SDL_FreeSurface(textSurface);
//		SDL_DestroyTexture(textTexture);

		// Update screen
		SDL_RenderPresent(renderer);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
//	manager.draw(); this used to draw the objects in order that they were created, we will now do it by group

	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& c : colliders) {
		c->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Byeee" << std::endl;
}

