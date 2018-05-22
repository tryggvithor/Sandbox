#ifndef UTILS_H
#define UTILS_H


#include <SDL.h>
#include <SDL_image.h>

namespace utils
{
	//Helpers

	//Concatenate two char * into a new malloced char *
	char *concat(const char *first, const char *second);


	//Primitives

	void renderFillRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect);
	void renderOutlineRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect);
	void renderHorizontalLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2);
	void renderVerticalDottedLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2, int interval);


	//Specific rendering functions

	void renderInViewport(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *viewportRect);


	//Loading things

	SDL_Texture *loadTexture(SDL_Renderer *renderer, char *filePath);
	SDL_Surface *loadSurface(SDL_Surface *screenSurface, char *filePath);

}


#endif // !UTILS_H
