#ifndef GLOBALS_H
#define GLOBALS_H

#include "Texture.h"

namespace globals
{
	bool hasQuit = false;
	int screenWidth = 1280;
	int screenHeight = 720;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	Texture *texture = new Texture();
	char *texturePath = "images/hairmansprites.png";
};

#endif // !GLOBALS_H