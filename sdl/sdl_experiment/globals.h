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
	static bool hasQuit = false;
	static const int LEVEL_WIDTH = 1280;
	static const int LEVEL_HEIGHT = 960;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	static const int SCREEN_FPS = 60;
	static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	static SDL_Renderer *renderer = NULL;
	static SDL_Window *window = NULL;
	static SDL_Surface *screenSurface = NULL;

	//Experiment specific stuff
	static Texture *backgroundTexture = NULL;
	static Texture *startTexture = NULL;
	static Texture *fpsTexture = NULL;
	static Texture *textTexture = NULL;
	static Texture *dotTextTexture = NULL;
	static Texture *pauseTexture = NULL;
	static Texture *dotTexture = NULL;
	static TTF_Font *font = NULL;
};


#endif // !GLOBALS_H