#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Globals.h"
#include "Utils.h"




bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(char* filePath);
SDL_Surface* loadSurface(char* filePath);




int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initalize\n");
		return 0;
	}
	if (!loadMedia())
	{
		printf("Failed to load media\n");
		return 0;
	}

	SDL_Event e;


	while (!Globals::hasQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				Globals::hasQuit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				
			}
		}

		SDL_SetRenderDrawColor(Globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Globals::renderer);



		SDL_RenderPresent(Globals::renderer);
	}

	close();
	return 0;
}




bool init()
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

	Globals::window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN);
	if (Globals::window == NULL)
	{
		printf("SDL_CreateWindow failed, error: %s\n", SDL_GetError());
		return false;
	}

	Globals::renderer = SDL_CreateRenderer(Globals::window, -1, SDL_RENDERER_ACCELERATED);
	if (Globals::renderer == NULL)
	{
		printf("SDL_CreateRenderer failed, error: %s\n", SDL_GetError());
		return false;
	}

	Globals::screenSurface = SDL_GetWindowSurface(Globals::window);

	return true;
}

bool loadMedia()
{
	Globals::texture = loadTexture(Globals::hairmanFilePath);
	if (Globals::texture == NULL)
	{
		printf("Failed to load texture image %s\n", Globals::hairmanFilePath);
		return false;
	}

	return true;
}

SDL_Texture* loadTexture(char* filePath)
{
	if (Globals::renderer == NULL)
	{
		printf("loadTexture() failed for %s, global renderer was NULL\n", filePath);
		return NULL;
	}
	SDL_Texture* newTexture = NULL;

	//Load the image
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	if (loadedSurface == NULL)
	{
		printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	//Create a texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(Globals::renderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("Failed to create texture from %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

SDL_Surface* loadSurface(char* filePath)
{
	if (Globals::screenSurface == NULL)
	{
		printf("loadSurface() failed for %s, global screenSurface was NULL\n", filePath);
		return NULL;
	}
	SDL_Surface* optimizedSurface = NULL;

	//Load the image
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	if (loadedSurface == NULL)
	{
		printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	//Optimize the loaded image to the correct format
	optimizedSurface = SDL_ConvertSurface(loadedSurface, Globals::screenSurface->format, NULL);
	if (optimizedSurface == NULL)
	{
		printf("Failed to optimize image %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	return optimizedSurface;
}

void close()
{
	//Textures
	SDL_DestroyTexture(Globals::texture);
	Globals::texture = NULL;

	//Window
	SDL_DestroyRenderer(Globals::renderer);
	SDL_DestroyWindow(Globals::window);
	Globals::renderer = NULL;
	Globals::window = NULL;

	//SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

