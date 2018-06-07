#include <stdio.h>
#include "globals.h"
#include "utils.h"
#include "Dot.h"

Dot::Dot(Texture *texture)
{
	this->texture = texture;

	posX = DOT_WIDTH/2;
	posY = DOT_HEIGHT/2;

	collider.x = posX - DOT_WIDTH/2;
	collider.y = posY - DOT_HEIGHT/2;
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
	double nextX = posX + velX * dt;
	double nextY = posY + velY * dt;

	collider.x = nextX - DOT_WIDTH/2;
	if (nextX < DOT_WIDTH/2 || nextX + DOT_WIDTH/2 > globals::SCREEN_WIDTH ||
		rect_collision(collider, wall))
	{
		nextX = posX;
		collider.x = nextX - DOT_WIDTH/2;
	}


	collider.y = nextY - DOT_HEIGHT/2;
	if (nextY < DOT_HEIGHT/2 || nextY + DOT_HEIGHT/2 > globals::SCREEN_HEIGHT ||
		rect_collision(collider, wall))
	{
		nextY = posY;
		collider.y = nextY - DOT_HEIGHT/2;
	}

	posX = nextX;
	posY = nextY;
}

void Dot::render()
{
	texture->render_at(posX - DOT_WIDTH/2, posY - DOT_HEIGHT/2);
}
