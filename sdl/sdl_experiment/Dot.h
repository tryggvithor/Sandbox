#ifndef DOT_H
#define DOT_H


#include <SDL.h>
#include "Texture.h"

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 10;

	int posX, posY;
	int velX, velY;
	SDL_Rect collider;

	Dot(Texture *texture);

	void handle_event(SDL_Event &e);

	void update(SDL_Rect &wall);

	void render();
private:
	Texture *texture;
};

#endif // !DOT_H
