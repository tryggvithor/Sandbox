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

	Texture *spriteSheet = new Texture();
	char *spriteSheetPath = "images/hairmansprites_transparent.png";
	SDL_Rect spriteClips[4] = {
		{  0,  0,200,200},
		{200,  0,200,200},
		{  0,200,200,200},
		{200,200,200,200}
	};
};

#endif // !GLOBALS_H