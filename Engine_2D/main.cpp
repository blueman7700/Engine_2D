#include "src/Game.h"
#include "src/imgui/imgui_sdl.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint64 frameStart;
	int frameTime;

	game = new Game();
	game->init("Alchemist Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks64();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks64() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
} 