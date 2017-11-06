#ifndef GLOBALS_H
#define GLOBALS_H

#include "Texture.h"

namespace globals
{
	int screenWidth = 1280;
	int screenHeight = 729;
	bool hasQuit = false;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	Texture *hairmanTexture = new Texture();
	Texture *backgroundTexture = new Texture();
	char *hairmanPath = "images/hairman2.png";
	char *backgroundPath = "images/test_image.png";
};


#endif // !GLOBALS_H