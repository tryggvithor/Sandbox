#include <SDL.h>
#include <stdio.h>
#include "Constants.h"


const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;


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

	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	SDL_Delay(3000);
	
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

	gWindow = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("SDL_CreateWindow failed, error: %s\n", SDL_GetError());
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	return true;
}

bool loadMedia()
{
	gHelloWorld = SDL_LoadBMP(Constants::IMG_TEST);
	if (gHelloWorld == NULL)
	{
		printf("Failed to load image %s, error: %s\n", Constants::IMG_TEST, SDL_GetError());
		return false;
	}

	return true;
}

void close()
{
	SDL_FreeSurface(gScreenSurface);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}