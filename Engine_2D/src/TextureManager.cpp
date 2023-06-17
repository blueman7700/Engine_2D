#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* filename)
{
	SDL_Surface* surf = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, surf);

	SDL_FreeSurface(surf);
	surf = nullptr;

	if (tex)
	{
		std::string out(filename);
		out = "Texture: \"" + out + "\" Loaded Successfully!";
		Logger::log(INFO, "Texture", out);
	}

	return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}