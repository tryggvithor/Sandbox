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
	printf("\n\n");

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
	char *extraText = NULL;
	char *dotText = NULL;
	Timer fpsTimer;
	Timer capTimer;

	fpsTimer.start();
	int countedFrames = 0;
	float overallAverageFPS = 0;


	//Experiment specific stuff
	SDL_Rect camera = {
		0, 0, 
		globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT
	};

	Dot dot = Dot(globals::dotTexture);
	Dot otherDot = Dot(globals::dotTexture, 
					   globals::LEVEL_WIDTH - globals::LEVEL_WIDTH/3, 
					   globals::LEVEL_HEIGHT - globals::LEVEL_HEIGHT/3);

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
		
			char text[64];

			SDL_snprintf(text, sizeof(text), "%.0f", averageLatestFPS);
			timeText = str_concat("FPS: ", text);
			if (!globals::fpsTexture->load_from_rendered_text(timeText, globals::font))
			{
				printf("Unable to render time texture!\n");
			}
			free(timeText);
			SDL_snprintf(text, sizeof(text), "%.0f, %.0f", otherDot.posX, otherDot.posY);
			extraText = str_concat("Other dot: ", text);
			if (!globals::textTexture->load_from_rendered_text(extraText, globals::font))
			{
				printf("Unable to render time texture!\n");
			}
			free(extraText);
			SDL_snprintf(text, sizeof(text), "%.0f, %.0f", dot.posX, dot.posY);
			dotText = str_concat("Dot: ", text);
			if (!globals::dotTextTexture->load_from_rendered_text(dotText, globals::font))
			{
				printf("Unable to render time texture!\n");
			}
			free(dotText);

			dot.update(dt, otherDot.collider);

			{//Camera update()?
				camera.x = (dot.posX + Dot::DOT_WIDTH / 2) - globals::SCREEN_WIDTH / 2;
				camera.y = (dot.posY + Dot::DOT_HEIGHT / 2) - globals::SCREEN_HEIGHT / 2;

				if (camera.x < 0)
				{
					camera.x = 0;
				}
				if (camera.y < 0)
				{
					camera.y = 0;
				}
				if (camera.x + camera.w > globals::LEVEL_WIDTH)
				{
					camera.x = globals::LEVEL_WIDTH - camera.w;
				}
				if (camera.y + camera.h > globals::LEVEL_HEIGHT)
				{
					camera.y = globals::LEVEL_HEIGHT - camera.h;
				}
			}
		}

		{//render()?
			SDL_SetRenderDrawColor(globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(globals::renderer);

			globals::backgroundTexture->render_at(0, 0, &camera);

			globals::fpsTexture->render_at(globals::SCREEN_WIDTH / 2 - globals::fpsTexture->width / 2, globals::SCREEN_HEIGHT / 2 - globals::fpsTexture->height);
			globals::textTexture->render_at(globals::SCREEN_WIDTH / 3 - globals::fpsTexture->width / 3, globals::SCREEN_HEIGHT / 3 - globals::fpsTexture->height);
			globals::dotTextTexture->render_at(globals::SCREEN_WIDTH / 3 - globals::fpsTexture->width / 3, globals::SCREEN_HEIGHT / 4 - globals::fpsTexture->height);


			dot.render(camera.x, camera.y);
			otherDot.render(0, 0);

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
		backgroundTexture = new Texture(renderer);
		startTexture = new Texture(renderer);
		pauseTexture = new Texture(renderer);
		fpsTexture = new Texture(renderer);
		textTexture = new Texture(renderer);
		dotTextTexture = new Texture(renderer);
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

		if (!backgroundTexture->load_from_file("images/weirdbackground.png"))
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
		delete backgroundTexture;
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

