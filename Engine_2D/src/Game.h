#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "imgui.h"
#include "imgui/imgui_sdl.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

#include <vector>
#include <iostream>

class ColliderComponent;

class Game 
{
public:

	Game();
	~Game();

	void init(const char* title, int x, int y, int w, int h, bool fullscreen);
	void handleEvents();
	void update();
	void updateUI();
	void render();
	void clean();
	
	bool running() { return isRunning; }
	static void addTileToMap(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:

	int count = 0;

	bool isRunning = false;
	SDL_Window* window = nullptr;

};

