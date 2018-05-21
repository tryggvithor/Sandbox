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

	//Experiment specific stuff
	


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

			//Handle button events
			for (int i = 0; i < globals::TOTAL_BUTTONS; ++i)
			{
				globals::buttons[i]->handleEvent(&e);
			}
		}

		SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(globals::renderer);

		for (int i = 0; i < globals::TOTAL_BUTTONS; i++)
		{
			globals::buttons[i]->render();
		}

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
	globals::buttonTexture = new Texture(globals::renderer);

	return true;
}

bool loadMedia(SDL_Renderer *renderer)
{
	if (!globals::buttonTexture->loadFromFile(globals::texturePath))
	{
		printf("lodaMedia failed, error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize clips
	for (int i = 0; i < Button::ButtonStates::COUNT; i++)
	{
		//400x400 texture, 2x2
		globals::buttonClips[i].x = (i % 2) * 200;
		globals::buttonClips[i].y = (i / 2) * 200;
		globals::buttonClips[i].w = 200;
		globals::buttonClips[i].h = 200;
	}

	//Initalize buttons
	for (int i = 0; i < globals::TOTAL_BUTTONS; i++)
	{
		globals::buttons[i] = new Button(globals::buttonTexture, globals::buttonClips, globals::BUTTON_WIDTH, globals::BUTTON_HEIGHT);
		globals::buttons[i]->pos.x = (i % 2) * globals::buttons[i]->width;
		globals::buttons[i]->pos.y = (i / 2) * globals::buttons[i]->height;
	}
	
	return true;
}


void close()
{
	//Textures
	delete globals::buttonTexture;

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

