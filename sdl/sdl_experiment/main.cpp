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
		return 1;
	}
	if (!loadMedia(globals::renderer))
	{
		printf("Failed to load media\n");
		return 1;
	}

	// Delta time
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	// Experiment specific stuff
	SDL_Event e;
	double angleDegrees = 0.0;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	Uint8 alphaMod = 255;

	while (!globals::hasQuit)
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

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
				case SDLK_a:
					angleDegrees -= 30;
					break;
				case SDLK_d:
					angleDegrees += 30;
					break;
				case SDLK_q:
					flipType = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_w:
					flipType = SDL_FLIP_NONE;
					break;
				case SDLK_e:
					flipType = SDL_FLIP_VERTICAL;
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(globals::renderer);

		globals::texture->renderAt(0, 0, NULL, angleDegrees, NULL, flipType);

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

	globals::renderer = SDL_CreateRenderer(globals::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (globals::renderer == NULL)
	{
		printf("SDL_CreateRenderer failed, error: %s\n", SDL_GetError());
		return false;
	}

	globals::screenSurface = SDL_GetWindowSurface(globals::window);
	globals::texture = new Texture(globals::renderer);

	return true;
}

bool loadMedia(SDL_Renderer *renderer)
{
	utils::Color transparentColor = {0x00, 0xff, 0xff, 0xff};


	if (!globals::texture->loadFromFile(transparentColor, globals::texturePath))
	{
		printf("Failed to load texture %s\n", globals::texturePath);
		return false;
	}

	return true;
}


void close()
{
	//Textures
	delete globals::texture;

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

