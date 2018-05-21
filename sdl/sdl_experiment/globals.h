#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
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
	Mix_Music *music = NULL;
	char *musicPath = "sounds/beat.wav";
	struct SoundEffects
	{
		Mix_Chunk *scratch = NULL;
		Mix_Chunk *high = NULL;
		Mix_Chunk *med = NULL;
		Mix_Chunk *low = NULL;
	} SoundEffects;
	struct SoundEffectPaths
	{
		char *scratch = "sounds/scratch.wav";
		char *high = "sounds/high.wav";
		char *med = "sounds/med.wav";
		char *low = "sounds/low.wav";
	} SoundEffectPaths;
	Texture *texture = NULL;
};

#endif // !GLOBALS_H