#ifndef GLOBALS_H
#define GLOBALS_H


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Texture.h"
#include "Timer.h"

namespace globals
{
	//Default stuff
	bool hasQuit = false;
	int screenWidth = 1280;
	int screenHeight = 720;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	//Experiment specific stuff
	Timer timer;
	const char *timeText = "Timer seconds: ";
	char *timeTextWithTime = NULL;
	Texture *startTexture = NULL;
	Texture *timeTexture = NULL;
	Texture *pauseTexture = NULL;
	TTF_Font *font = NULL;

	void cleanUp()
	{
		//Textures
		delete globals::startTexture;
		delete globals::timeTexture;
		delete globals::pauseTexture;

		//Window
		SDL_DestroyRenderer(globals::renderer);
		SDL_DestroyWindow(globals::window);
		globals::renderer = NULL;
		globals::window = NULL;
		globals::screenSurface = NULL;
	}
};


#endif // !GLOBALS_H