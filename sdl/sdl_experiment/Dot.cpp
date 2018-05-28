#include <stdio.h>
#include "globals.h"
#include "utils.h"
#include "Dot.h"

Dot::Dot(Texture *texture)
{
	this->texture = texture;

	posX = 0;
	posY = 0;

	collider.x = 0;
	collider.y = 0;
	collider.w = DOT_WIDTH;
	collider.h = DOT_HEIGHT;

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

void Dot::update(SDL_Rect &wall)
{
	posX += velX;
	collider.x = posX;

	if (posX < 0 || posX + DOT_WIDTH > globals::SCREEN_WIDTH ||
		utils::rectCollision(collider, wall))
	{
		posX -= velX;
		collider.x = posX;
	}


	posY += velY;
	collider.y = posY;

	if (posY < 0 || posY + DOT_HEIGHT > globals::SCREEN_HEIGHT || 
		utils::rectCollision(collider, wall))
	{
		posY -= velY;
		collider.y = posY;
	}
}

void Dot::render()
{
	texture->renderAt(posX, posY);
}
