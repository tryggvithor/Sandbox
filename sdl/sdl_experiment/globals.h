#ifndef GLOBALS_H
#define GLOBALS_H

#include "Texture.h"

namespace globals
{
	// Defaults
	bool hasQuit = false;
	int screenWidth = 1280;
	int screenHeight = 720;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	// Experiment specific
	Texture *texture = NULL;
	char *texturePath = "images/hairman2.png";
};

#endif // !GLOBALS_H