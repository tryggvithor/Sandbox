#ifndef GLOBALS_H
#define GLOBALS_H

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
	int totalTextures = 5;
	struct Bools
	{
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
	} ShouldRender;
	struct Textures
	{
		Texture *upTexture = NULL;
		Texture *downTexture = NULL;
		Texture *leftTexture = NULL;
		Texture *rightTexture = NULL;
		Texture *defaultTexture = NULL;
	} ArrowTextures;
	struct TexturePaths
	{
		char *upPath = "images/up.png";
		char *downPath = "images/down.png";
		char *leftPath = "images/left.png";
		char *rightPath = "images/right.png";
		char *defaultPath = "images/default.png";
	} ArrowPaths;
};

#endif // !GLOBALS_H