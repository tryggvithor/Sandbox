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
	printf("\n");

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

	//Delta time
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;



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
					printf("Nice");
					break;
				default:
					break;
				}
			}

			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			globals::ShouldRender.up = currentKeyStates[SDL_SCANCODE_UP];
			globals::ShouldRender.down = currentKeyStates[SDL_SCANCODE_DOWN];
			globals::ShouldRender.left = currentKeyStates[SDL_SCANCODE_LEFT];
			globals::ShouldRender.right = currentKeyStates[SDL_SCANCODE_RIGHT];
		}

		SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(globals::renderer);

		globals::ArrowTextures.defaultTexture->renderAt(0, 0);
		if (globals::ShouldRender.up) globals::ArrowTextures.upTexture->renderAt(0, 0);
		if (globals::ShouldRender.down) globals::ArrowTextures.downTexture->renderAt(0, 0);
		if (globals::ShouldRender.left) globals::ArrowTextures.leftTexture->renderAt(0, 0);
		if (globals::ShouldRender.right) globals::ArrowTextures.rightTexture->renderAt(0, 0);

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
	
#ifdef _SDL_TTF_H
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf failed to initialize, error: %s\n", TTF_GetError());
		return false;
	}
#endif

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
	globals::ArrowTextures.upTexture = new Texture(globals::renderer);
	globals::ArrowTextures.downTexture = new Texture(globals::renderer);
	globals::ArrowTextures.leftTexture = new Texture(globals::renderer);
	globals::ArrowTextures.rightTexture = new Texture(globals::renderer);
	globals::ArrowTextures.defaultTexture = new Texture(globals::renderer);
	

	return true;
}

bool loadMedia(SDL_Renderer *renderer)
{
	SDL_Color transparentColor = {0xFF, 0xFF, 0xFF, 0xFF};
	if (!globals::ArrowTextures.upTexture->loadFromFile(globals::ArrowPaths.upPath, &transparentColor))
	{
		printf("loadMedia failed, error: %s\n", SDL_GetError());
		return false;
	}
	if (!globals::ArrowTextures.downTexture->loadFromFile(globals::ArrowPaths.downPath, &transparentColor))
	{
		printf("loadMedia failed, error: %s\n", SDL_GetError());
		return false;
	}
	if (!globals::ArrowTextures.leftTexture->loadFromFile(globals::ArrowPaths.leftPath, &transparentColor))
	{
		printf("loadMedia failed, error: %s\n", SDL_GetError());
		return false;
	}
	if (!globals::ArrowTextures.rightTexture->loadFromFile(globals::ArrowPaths.rightPath, &transparentColor))
	{
		printf("loadMedia failed, error: %s\n", SDL_GetError());
		return false;
	}
	if (!globals::ArrowTextures.defaultTexture->loadFromFile(globals::ArrowPaths.defaultPath, &transparentColor))
	{
		printf("loadMedia failed, error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}


void close()
{
	//Textures
	delete globals::ArrowTextures.upTexture;
	delete globals::ArrowTextures.downTexture;
	delete globals::ArrowTextures.leftTexture;
	delete globals::ArrowTextures.rightTexture;
	delete globals::ArrowTextures.defaultTexture;

	//Window
	SDL_DestroyRenderer(globals::renderer);
	SDL_DestroyWindow(globals::window);
	globals::renderer = NULL;
	globals::window = NULL;
	globals::screenSurface = NULL;

	//SDL subsystems
#ifdef _SDL_TTF_H
	if (TTF_WasInit()) TTF_Quit();
#endif
	IMG_Quit();
	SDL_Quit();
}

