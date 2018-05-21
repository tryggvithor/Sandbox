#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

	//Experiment specific stuff
	const int BUTTON_WIDTH = 300;
	const int BUTTON_HEIGHT = 200;
	const int TOTAL_BUTTONS = globals::MouseEvents::COUNT;


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
				//Current problem with this approach:
				//	More than one key at a time -> only the latest key gets handled and the rest is ignored
				//Handle this differently in the future 
				//	with an array of keys instead, SDL_GetKeyboardState(NULL)?
				switch (e.key.keysym.sym)
				{
				case SDLK_a:
					printf("Nice");
					break;
				default:
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(globals::renderer);

		globals::texture->renderAt(0, 0);

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
	
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf failed to initialize, error: %s\n", TTF_GetError());
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
	SDL_Color transparentColor = {0x00, 0xff, 0xff, 0xff};

	globals::font = TTF_OpenFont(globals::fontPath, 28);
	if (globals::font == NULL)
	{
		printf("loadMedia failed, error: %s\n", TTF_GetError());
		return false;
	}
	
	SDL_Color textColor = {0,0,0};
	if (!globals::texture->loadFromRenderedText("The quickest of the brownest foxes jumps over the laziest of all dogs.", globals::font, textColor))
	{
		printf("lodaMedia failed, error: %s\n", SDL_GetError());
		return false;
	}
	
	return true;
}


void close()
{
	//Textures
	delete globals::texture;

	//TTF
	TTF_CloseFont(globals::font);
	globals::font = NULL;

	//Window
	SDL_DestroyRenderer(globals::renderer);
	SDL_DestroyWindow(globals::window);
	globals::renderer = NULL;
	globals::window = NULL;
	globals::screenSurface = NULL;

	//SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

