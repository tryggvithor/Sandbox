#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include "Texture.h"

class Button
{
public:
	enum ButtonStates
	{
		MOUSE_OUT = 0,
		MOUSE_OVER_MOTION = 1,
		MOUSE_DOWN = 2,
		MOUSE_UP = 3,
		COUNT = 4
	};

	// Top left position
	SDL_Point pos;
	int width, height;

	Button(Texture *texture, SDL_Rect *textureClips, int width, int height);
	~Button();

	void handleEvent(SDL_Event *e);
	void render();

private:
	ButtonStates currentState;
	Texture *texture;
	SDL_Rect *textureClips;
};

#endif // !BUTTON_H
