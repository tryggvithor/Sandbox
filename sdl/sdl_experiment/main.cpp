#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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
	Uint32 startTime = 0;


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
				case SDLK_RETURN:
					startTime = SDL_GetTicks();
					break;
				default:
					break;
				}
			}

			//const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		}
		
		char time[34];
		SDL_itoa(SDL_GetTicks() - startTime, time, 10);
		globals::timeTextWithTime = utils::concat(globals::timeText, time);
		if (!globals::timeTexture->loadFromRenderedText(globals::timeTextWithTime, globals::font))
		{
			printf("Unable to render time texture!\n");
		}

		SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(globals::renderer);

		globals::infoTexture->renderAt(globals::screenWidth/2 - globals::infoTexture->width/2, 0);
		globals::timeTexture->renderAt(globals::screenWidth/2 - globals::timeTexture->width/2, globals::screenHeight/2 - globals::timeTexture->height);

		SDL_RenderPresent(globals::renderer);
	}

	close();
	return 0;
}


bool init(int screenWidth, int screenHeight)
{
	bool succeeded = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL failed to initialize, error: %s\n", SDL_GetError());
		succeeded = false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed to initialize, error: %s\n", IMG_GetError());
		succeeded = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer failed to initialize, error: %s\n", Mix_GetError());
		succeeded = false;
	}
	
#ifdef _SDL_TTF_H
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf failed to initialize, error: %s\n", TTF_GetError());
		succeeded = false;
	}
#endif

	globals::window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (globals::window == NULL)
	{
		printf("SDL_CreateWindow failed, error: %s\n", SDL_GetError());
		succeeded = false;
	}

	globals::renderer = SDL_CreateRenderer(globals::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (globals::renderer == NULL)
	{
		printf("SDL_CreateRenderer failed, error: %s\n", SDL_GetError());
		succeeded = false;
	}

	globals::screenSurface = SDL_GetWindowSurface(globals::window);
	globals::infoTexture = new Texture(globals::renderer);
	globals::timeTexture = new Texture(globals::renderer);

	return succeeded;
}


bool loadMedia(SDL_Renderer *renderer)
{
	bool succeeded = true;

	globals::font = TTF_OpenFont("fonts/ClassCoder.ttf", 32);
	if (globals::font == NULL)
	{
		printf("loadMedia failed, error: %s\n", TTF_GetError());
		succeeded = false;
	}

	if (!globals::infoTexture->loadFromRenderedText("Press Enter to reset the start time", globals::font))
	{
		printf("loadMedia failed, error: %s\n", SDL_GetError());
		succeeded = false;
	}

	return succeeded; 
}


void close()
{
	//Textures
	delete globals::infoTexture;
	delete globals::timeTexture;
	free(globals::timeTextWithTime);

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
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

