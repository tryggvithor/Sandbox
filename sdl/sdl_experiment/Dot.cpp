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

	numColliders = 6;
	colliders = new SDL_Rect[numColliders];

	colliders[0].w = 6;
	colliders[0].h = 20;

	colliders[1].w = 10;
	colliders[1].h = 18;

	colliders[2].w = 14;
	colliders[2].h = 16;

	colliders[3].w = 16;
	colliders[3].h = 14;

	colliders[4].w = 18;
	colliders[4].h = 10;

	colliders[5].w = 20;
	colliders[5].h = 6;


	this->update_colliders(posX, posY);
}

Dot::~Dot()
{
	delete[] colliders;
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

void Dot::update(double dt, SDL_Rect &wall, SDL_Rect *otherColliders)
{
	double nextX = posX + velX * dt;
	double nextY = posY + velY * dt;

	this->update_colliders(nextX, posY);
	if (nextX < DOT_WIDTH/2 || nextX + DOT_WIDTH/2 > globals::SCREEN_WIDTH ||
		rect_arrays_collision(colliders, &wall, numColliders, 1) || 
		rect_arrays_collision(colliders, otherColliders, numColliders, numColliders))
	{
		nextX = posX;
		this->update_colliders(nextX, posY);
	}


	this->update_colliders(posX, nextY);
	if (nextY < DOT_HEIGHT/2 || nextY + DOT_HEIGHT/2 > globals::SCREEN_HEIGHT ||
		rect_arrays_collision(colliders, &wall, numColliders, 1) ||
		rect_arrays_collision(colliders, otherColliders, numColliders, numColliders))
	{
		nextY = posY;
		this->update_colliders(posX, nextY);
	}

	posX = nextX;
	posY = nextY;
}

void Dot::render()
{
	texture->render_at(posX - DOT_WIDTH/2, posY - DOT_HEIGHT/2);
}

void Dot::update_colliders(double posX, double posY)
{
	//A bunch of rectangles in a circle
	for (int i = 0; i < numColliders; ++i)
	{
		colliders[i].x = posX - colliders[i].w / 2;
		colliders[i].y = posY - colliders[i].h / 2;
	}
}