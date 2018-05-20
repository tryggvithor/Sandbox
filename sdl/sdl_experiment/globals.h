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

	const int colorAnimationFrames = 16;
	SDL_Rect spriteClips[colorAnimationFrames];
	Texture *colorAnimationTexture = NULL;
	char *colorAnimationPath = "images/color_animation.png";
};

#endif // !GLOBALS_H