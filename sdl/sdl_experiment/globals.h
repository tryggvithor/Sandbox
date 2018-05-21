#ifndef GLOBALS_H
#define GLOBALS_H

#include "Texture.h"
#include "Button.h"

namespace globals
{
	//Defaults
	bool hasQuit = false;
	int screenWidth = 1280;
	int screenHeight = 720;
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	//Experiment specific
	const int BUTTON_WIDTH = 200;
	const int BUTTON_HEIGHT = 200;
	const int TOTAL_BUTTONS = 4;
	Button *buttons[TOTAL_BUTTONS];

	Texture *buttonTexture = NULL;
	SDL_Rect buttonClips[Button::ButtonStates::COUNT];
	char *texturePath = "images/hairmansprites_buttons.png";
};

#endif // !GLOBALS_H