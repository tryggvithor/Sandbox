#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Texture.h"
#include "globals.h"
#include "utils.h"


bool init(int screenWidth, int screenHeight);
bool loadMedia(SDL_Renderer *renderer);
void close();




int main(int argc, char *args[])
{
	if (!init(globals::screenWidth, globals::screenHeight))
	{
		printf("Failed to initalize\n");
		return 0;
	}
	if (!loadMedia(globals::renderer))
	{
		printf("Failed to load media\n");
		return 0;
	}

	SDL_Event e;


	Uint8 alphaMod = 255;

	while (!globals::hasQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				globals::hasQuit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_w: 
					if (alphaMod + 32 > 255)
					{
						alphaMod = 255;
					}
					else alphaMod += 32;
					break;
				case SDLK_s: 
					if (alphaMod - 32 < 0)
					{
						alphaMod = 0;
					}
					else alphaMod -= 32;
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(globals::renderer);

		globals::fadeinTexture->renderAt(globals::renderer, 0, 0);

		globals::fadeoutTexture->setAlpha(alphaMod);
		globals::fadeoutTexture->renderAt(globals::renderer, 0, 0);

		SDL_RenderPresent(globals::renderer);
	}

	close();
	return 0;
}




bool init(int screenWidth, int screenHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_INIT failed, error: %s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed to initialize, error: %s\n", IMG_GetError());
		return false;
	}

	globals::window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (globals::window == NULL)
	{
		printf("SDL_CreateWindow failed, error: %s\n", SDL_GetError());
		return false;
	}

	globals::renderer = SDL_CreateRenderer(globals::window, -1, SDL_RENDERER_ACCELERATED);
	if (globals::renderer == NULL)
	{
		printf("SDL_CreateRenderer failed, error: %s\n", SDL_GetError());
		return false;
	}

	globals::screenSurface = SDL_GetWindowSurface(globals::window);

	return true;
}

bool loadMedia(SDL_Renderer *renderer)
{
	utils::Color transparentColor = {0x00, 0xff, 0xff, 0xff};


	if (!globals::fadeinTexture->loadFromFile(renderer, transparentColor, globals::fadeinPath))
	{
		printf("Failed to load texture %s\n", globals::fadeinPath);
		return false;
	}

	if (!globals::fadeoutTexture->loadFromFile(renderer, transparentColor, globals::fadeoutPath))
	{
		printf("Failed to load texture %s\n", globals::fadeoutPath);
		return false;
	}

	globals::fadeoutTexture->setBlendMode(SDL_BLENDMODE_BLEND);

	return true;
}


void close()
{
	//Textures
	delete globals::fadeinTexture;
	delete globals::fadeoutTexture;


	//Window
	SDL_DestroyRenderer(globals::renderer);
	SDL_DestroyWindow(globals::window);
	globals::renderer = NULL;
	globals::window = NULL;
	globals::screenSurface = NULL;


	//SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

