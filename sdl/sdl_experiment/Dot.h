#ifndef DOT_H
#define DOT_H


#include <SDL.h>
#include "Texture.h"

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 100;

	double posX, posY;
	double velX, velY;
	//Maybe instead we want the collider position to point to the position struct of this class? 
	//Maybe we want a more general Collider structure?
	SDL_Rect *colliders; 
	int numColliders;

	Dot(Texture *texture, double posX = DOT_WIDTH/2, double posY = DOT_HEIGHT/2);
	~Dot();

	void handle_event(SDL_Event &e);
	void update(double dt, SDL_Rect &wall, SDL_Rect *otherColliders);
	void render();
private:
	Texture *texture;

	void update_colliders(double posX, double posY);
};

#endif // !DOT_H
