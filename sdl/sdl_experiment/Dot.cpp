#include <stdio.h>
#include "globals.h"
#include "Dot.h"

Dot::Dot(Texture *texture)
{
	this->texture = texture;
	posX = 0;
	posY = 0;
	velX = 0;
	velY = 0;
}

void Dot::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY -= DOT_VEL; 
			break;
		case SDLK_DOWN:
			velY += DOT_VEL;
			break;
		case SDLK_LEFT:
			velX -= DOT_VEL;
			break;
		case SDLK_RIGHT:
			velX += DOT_VEL;
			break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			velY += DOT_VEL;
			break;
		case SDLK_DOWN:
			velY -= DOT_VEL;
			break;
		case SDLK_LEFT:
			velX += DOT_VEL;
			break;
		case SDLK_RIGHT:
			velX -= DOT_VEL;
			break;
		}
	}
}

void Dot::update()
{
	posX += velX;
	posY += velY;

	{//wrap(posx, posy)
		if (posX < 0) posX = globals::SCREEN_WIDTH - DOT_WIDTH;
		if (posX + DOT_WIDTH > globals::SCREEN_WIDTH) posX = 0;

		if (posY < 0) posY = globals::SCREEN_HEIGHT - DOT_HEIGHT;
		if (posY + DOT_HEIGHT > globals::SCREEN_HEIGHT) posY = 0;
	}
}

void Dot::render()
{
	texture->renderAt(posX, posY);
}
