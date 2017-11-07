#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>


namespace utils
{
	struct Color { Uint8 r, g, b, a; };
	struct Position { int x, y; };


	//Primitives
	void renderFillRect(SDL_Renderer *renderer, Color color, SDL_Rect rect);
	void renderOutlineRect(SDL_Renderer *renderer, Color color, SDL_Rect rect);
	void drawHorizontalLine(SDL_Renderer *renderer, Color color, Position pos1, Position pos2);
	void drawVerticalDottedLine(SDL_Renderer *renderer, Color color, Position pos1, Position pos2, int interval);


	//Rendering functions
	void renderInViewport(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *viewportRect);


	//Loading things
	SDL_Texture *loadTexture(SDL_Renderer *renderer, char *filePath);
	SDL_Surface *loadSurface(SDL_Surface *screenSurface, char *filePath);
}


#endif // !UTILS_H
