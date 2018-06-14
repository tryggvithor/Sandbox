#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "Texture.h"
#include "Timer.h"
#include "Dot.h"

#include "globals.h"
#include "utils.h"


bool init();
bool load_media();
void close();




int main(int argc, char *args[])
{
	printf("\n");

	if (!init())
	{
		printf("Failed to initalize\n");
		return 0;
	}
	if (!load_media())
	{
		printf("Failed to load media\n");
		return 0;
	}

	SDL_Event e;
	Uint8 alphaMod = 255;

	//Delta time
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double dt = 0;

	const int FPScount = 30;
	double latestFPSs[FPScount] = {};
	int latestFPSindex = 0;
	double averageLatestFPS = 0;

	char *timeText = NULL;
	Timer fpsTimer;
	Timer capTimer;

	fpsTimer.start();
	int countedFrames = 0;
	float overallAverageFPS = 0;


	//Experiment specific stuff
	Dot dot = Dot(globals::dotTexture);
	Dot otherDot = Dot(globals::dotTexture, 
					   globals::SCREEN_WIDTH - globals::SCREEN_WIDTH/3, 
					   globals::SCREEN_HEIGHT - globals::SCREEN_HEIGHT/3);
	SDL_Rect wall = {
		300,40,
		40,400
	};

	while (!globals::hasQuit)
	{
		capTimer.start();

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		dt = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
		latestFPSs[latestFPSindex] = 1000.f / dt / 1000.f;
		latestFPSindex = ++latestFPSindex % FPScount;

		{//handleInputs(e)?
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
					case SDLK_s:
						printf("Nice\n");
					default:
						break;
					}
				}

				//const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

				dot.handle_event(e);
			}
		}

		{//update(deltaTime)?
			overallAverageFPS = countedFrames / (fpsTimer.get_ticks() / 1000.f);
			if (overallAverageFPS > 1000000)
			{
				overallAverageFPS = 0.0f;
			}

			averageLatestFPS = 0;
			for (int i = 0; i < FPScount; i++)
			{
				averageLatestFPS += latestFPSs[i];
			}
			averageLatestFPS = averageLatestFPS / FPScount;
		
			char fpsText[64];
			SDL_snprintf(fpsText, sizeof(fpsText), "%.0f", averageLatestFPS);

			timeText = str_concat("FPS: ", fpsText);
			if (!globals::fpsTexture->load_from_rendered_text(timeText, globals::font))
			{
				printf("Unable to render time texture!\n");
			}
			free(timeText);

			dot.update(dt, wall, otherDot.collider);
		}

		{//render()?
			SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(globals::renderer);

			globals::fpsTexture->render_at(globals::SCREEN_WIDTH / 2 - globals::fpsTexture->width / 2, globals::SCREEN_HEIGHT / 2 - globals::fpsTexture->height);

			render_fill_rect(globals::renderer, {0x7F,0x7F,0xFF,0xFF}, wall);
			render_outline_rect(globals::renderer, {0,0,0,0xFF}, wall);

			dot.render();
			otherDot.render();

			SDL_RenderPresent(globals::renderer);
		}


		countedFrames++;
		int frameTicks = capTimer.get_ticks();
		if (frameTicks < globals::SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(globals::SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	close();
	return 0;
}


bool init()
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

	{
		using namespace globals;

		window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("SDL_CreateWindow failed, error: %s\n", SDL_GetError());
			succeeded = false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			printf("SDL_CreateRenderer failed, error: %s\n", SDL_GetError());
			succeeded = false;
		}
	
		screenSurface = SDL_GetWindowSurface(window);
		startTexture = new Texture(renderer);
		pauseTexture = new Texture(renderer);
		fpsTexture = new Texture(renderer);
		dotTexture = new Texture(renderer);
	}

	return succeeded;
}


bool load_media()
{
	bool succeeded = true;

	{
		using namespace globals;

		font = TTF_OpenFont("fonts/ClassCoder.ttf", 32);
		if (font == NULL)
		{
			printf("loadMedia failed, error: %s\n", TTF_GetError());
			succeeded = false;
		}

		if (!startTexture->load_from_rendered_text("Press S to start/stop the timer", font))
		{
			printf("loadMedia failed, error: %s\n", SDL_GetError());
			succeeded = false;
		}

		if (!pauseTexture->load_from_rendered_text("Press P to pause/unpause the timer", font))
		{
			printf("loadMedia failed, error: %s\n", SDL_GetError());
			succeeded = false;
		}

		SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};
		if (!dotTexture->load_from_file("images/dot.bmp", &color))
		{
			printf("loadMedia failed, error: %s\n", SDL_GetError());
			succeeded = false;
		}
	}

	return succeeded; 
}


void close()
{
	{
		using namespace globals;

		//Textures
		delete startTexture;
		delete fpsTexture;
		delete pauseTexture;
		delete dotTexture;

		//Window
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		renderer = NULL;
		window = NULL;
		screenSurface = NULL;
	}

	//SDL subsystems
#ifdef _SDL_TTF_H
	if (TTF_WasInit()) TTF_Quit();
#endif
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

