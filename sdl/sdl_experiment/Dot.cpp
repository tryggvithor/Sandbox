#include <stdio.h>
#include "globals.h"
#include "utils.h"
#include "Dot.h"

Dot::Dot(Texture *texture, double posX, double posY)
{
	this->texture = texture;

	this->posX = posX;
	this->posY = posY;

	velX = 0;
	velY = 0;

	collider.r = DOT_WIDTH / 2;


	this->update_colliders(posX, posY);
}

Dot::~Dot()
{
	
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

void Dot::update(double dt, Circle &circle)
{
	double nextX = posX + velX * dt;
	double nextY = posY + velY * dt;

	this->update_colliders(nextX, posY);
	if (nextX < DOT_WIDTH/2 || nextX + DOT_WIDTH/2 > globals::LEVEL_WIDTH ||
		circle_collision(collider, circle))
	{
		nextX = posX;
		this->update_colliders(nextX, posY);
	}


	this->update_colliders(posX, nextY);
	if (nextY < DOT_HEIGHT/2 || nextY + DOT_HEIGHT/2 > globals::LEVEL_HEIGHT ||
		circle_collision(collider, circle))
	{
		nextY = posY;
		this->update_colliders(posX, nextY);
	}

	posX = nextX;
	posY = nextY;
}

void Dot::render(double camX, double camY)
{
	texture->render_at(posX - DOT_WIDTH/2 - camX, posY - DOT_HEIGHT/2 - camY);
}

void Dot::update_colliders(double posX, double posY)
{
	this->collider.x = posX;
	this->collider.y = posY;
}