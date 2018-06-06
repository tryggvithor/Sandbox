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

void Dot::handle_event(SDL_Event & e)
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

void Dot::update(double dt, SDL_Rect &wall)
{
	double frameVelX = velX * dt;
	double frameVelY = velY * dt;

	posX += frameVelX;
	collider.x = posX;

	if (posX < 0 || posX + DOT_WIDTH > globals::SCREEN_WIDTH ||
		rect_collision(collider, wall))
	{
		posX -= frameVelX;
	}


	posY += frameVelY;
	collider.y = posY;

	if (posY < 0 || posY + DOT_HEIGHT > globals::SCREEN_HEIGHT || 
		rect_collision(collider, wall))
	{
		posY -= frameVelY;
	}
}

void Dot::render()
{
	texture->render_at(posX, posY);
}
