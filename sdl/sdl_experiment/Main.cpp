#include <SDL.h>
#include <stdio.h>
#include "Globals.h"


bool init();
bool loadMedia();
void close();
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
	Globals::currentSurface = Globals::arrowKeySurfaces[Globals::ArrowKeySurface::DEFAULT];
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = Globals::screenWidth;
	stretchRect.h = Globals::screenHeight;

	while (!Globals::hasQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				Globals::hasQuit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					Globals::currentSurface = Globals::arrowKeySurfaces[Globals::ArrowKeySurface::UP];
					break;
				case SDLK_DOWN:
					Globals::currentSurface = Globals::arrowKeySurfaces[Globals::ArrowKeySurface::DOWN];
					break;
				case SDLK_LEFT:
					Globals::currentSurface = Globals::arrowKeySurfaces[Globals::ArrowKeySurface::LEFT];
					break;
				case SDLK_RIGHT:
					Globals::currentSurface = Globals::arrowKeySurfaces[Globals::ArrowKeySurface::RIGHT];
					break;
				}
			}
		}

		SDL_BlitScaled(Globals::currentSurface, NULL, Globals::screenSurface, NULL);
		SDL_BlitSurface(Globals::currentSurface, NULL, Globals::screenSurface, NULL);
		SDL_UpdateWindowSurface(Globals::window);
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

	Globals::window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN);
	if (Globals::window == NULL)
	{
		printf("SDL_CreateWindow failed, error: %s\n", SDL_GetError());
		return false;
	}

	Globals::screenSurface = SDL_GetWindowSurface(Globals::window);

	return true;
}

bool loadMedia()
{
	for (int i = 0; i < Globals::ArrowKeySurface::COUNT; i++)
	{
		Globals::arrowKeySurfaces[i] = loadSurface(Globals::arrowKeyFilePaths[i]);
		if (Globals::arrowKeySurfaces[i] == NULL)
		{
			return false;
		}
	}

	return true;
}

SDL_Surface* loadSurface(char* filePath)
{
	SDL_Surface* optimizedSurface = NULL;

	//Load image
	SDL_Surface* loadedSurface = SDL_LoadBMP(filePath);
	if (loadedSurface == NULL)
	{
		printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	//Optimize the loaded image
	optimizedSurface = SDL_ConvertSurface(loadedSurface, Globals::screenSurface->format, NULL);
	if (optimizedSurface == NULL)
	{
		printf("Failed to optimize image %s, error: %s\n", filePath, SDL_GetError());
	}

	return optimizedSurface;
}

void close()
{
	SDL_FreeSurface(Globals::screenSurface);
	
	for (int i = 0; i < Globals::ArrowKeySurface::COUNT-1; i++)
	{
		SDL_FreeSurface(Globals::arrowKeySurfaces[i]);
		Globals::arrowKeySurfaces[i] = NULL;
	}

	SDL_DestroyWindow(Globals::window);
	Globals::window = NULL;

	SDL_Quit();
}