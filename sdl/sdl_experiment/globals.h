#ifndef GLOBALS_H
#define GLOBALS_H


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Texture.h"
#include "Button.h"

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
	const char *timeText = "Milliseconds since start time: ";
	char * timeTextWithTime = NULL;
	Texture *infoTexture = NULL;
	Texture *timeTexture = NULL;
	TTF_Font *font = NULL;
};


#endif // !GLOBALS_H