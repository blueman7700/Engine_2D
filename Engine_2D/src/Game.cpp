#include "Game.h"
#include "Logger.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "ECS/Components.hpp"
#include "Vector2D.h"
#include "Collision.h"

TileMap* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

bool showWidget = true;

enum GroupLabels : std::size_t 
{
	BACKGROUND_GROUP,
	MAP_GROUP,
	PLAYER_GROUP,
	OBJECT_GROUP,
	ENTITY_GROUP,
	COLLIDER_GROUP
};

/// <summary>
/// 
/// </summary>
Game::Game() 
{

}

/// <summary>
/// 
/// </summary>
Game::~Game()
{
	clean();
}

/// <summary>
/// 
/// </summary>
/// <param name="title"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="fullscreen"></param>
void Game::init(const char* title, int x, int y, int w, int h, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL subsystems
	// in future maybe use assertions instead??
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		Logger::log(INFO, "Engine", "SDL Subsystem Initialized!");
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io{ ImGui::GetIO() };

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		// Create window and check for errors.
		window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (window)
		{
			Logger::log(INFO, "Engine", "Window Created!");
		}

		// Create renderer and check for errors.
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			Logger::log(INFO, "Engine", "Renderer Created!");
		}

		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer_Init(renderer);

		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}

	map = new TileMap();

	TileMap::loadMap("assets/maps/test.csv", 16, 16);

	try 
	{
		// TODO: make a player class that stores all of this
		player.addComponent<TransformComponent>(0, 0, 3.0f);
		player.addComponent<AnimationComponent>("assets/spritesheets/player_base.png", 64, 2);
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("player", player.getComponent<AnimationComponent>());
		player.addGroup(PLAYER_GROUP);
		Animation idle = Animation(0, 1, 1000);
		Animation walkRight = Animation(6, 6, 135);
		Animation walkLeft = Animation(7, 6, 135);
		Animation walkUp = Animation(5, 6, 135);
		Animation walkDown = Animation(4, 6, 135);
		player.getComponent<AnimationComponent>().addAnimation(idle, "IDLE");
		player.getComponent<AnimationComponent>().addAnimation(walkUp, "WALK_UP");
		player.getComponent<AnimationComponent>().addAnimation(walkDown, "WALK_DOWN");
		player.getComponent<AnimationComponent>().addAnimation(walkRight, "WALK_RIGHT");
		player.getComponent<AnimationComponent>().addAnimation(walkLeft, "WALK_LEFT");
		player.getComponent<AnimationComponent>().setAnimation("IDLE");
		player.getComponent<AnimationComponent>().start();

		wall.addComponent<TransformComponent>(32*16, 32*16, 0);
		wall.addComponent<SpriteComponent>("assets/tilemaps/tm_stone.png", 32 * 3, 32 * 3, 32, 32);
		wall.addComponent<ColliderComponent>("wall", wall.getComponent<SpriteComponent>());
		wall.addGroup(COLLIDER_GROUP);
	}
	catch (const std::exception& e)
	{
		Logger::logException(e);
	}
}

/// <summary>
/// 
/// </summary>
void Game::handleEvents()
{
	SDL_PollEvent(&event);
	ImGui_ImplSDL2_ProcessEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

/// <summary>
/// 
/// </summary>
void Game::update()
{
	manager.clean();
	manager.update();

	auto& playerTransform = player.getComponent<TransformComponent>();

	for (auto c : colliders)
	{
		if (c->tag != "player")
		{
			if (Collision::AABB(player.getComponent<ColliderComponent>(), *c))
			{
				// TODO: handle player collision.
			}

		}
	}
}

void Game::updateUI()
{
	if (showWidget)
	{
		ImGui::Begin("a panel", &showWidget);
		ImGui::Text("Hello World");
		ImGui::End();

		ImGui::Begin("another panel", &showWidget);
		ImGui::Button("button");
		ImGui::End();

		ImGui::ShowMetricsWindow();
	}
}

auto& tileGroup(manager.getGroup(MAP_GROUP));
auto& playerGroup(manager.getGroup(PLAYER_GROUP));
auto& colliderGroup(manager.getGroup(COLLIDER_GROUP));

/// <summary>
/// 
/// </summary>
void Game::render() 
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	updateUI();

	ImGui::Render();

	SDL_RenderClear(renderer);
	// TODO: add rendering code here...

	for (auto& t : tileGroup)
	{
		t->draw();
	}
	for (auto& p : playerGroup)
	{
		p->draw();
	}
	for (auto& c : colliderGroup)
	{
		c->draw();
	}

	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(renderer);
}

/// <summary>
/// 
/// </summary>
void Game::clean() 
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	Logger::log(INFO, "Engine", "Game Cleaned!");
}

void Game::addTileToMap(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TransformComponent>(x, y);
	tile.addComponent<TileComponent>(id);
	tile.addGroup(MAP_GROUP);
}