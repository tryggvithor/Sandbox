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
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	const int SCREEN_FPS = 60; 
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	//Experiment specific stuff
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