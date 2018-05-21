#include "utils.h"

namespace utils
{
	//Primitives
	void renderFillRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}

	void renderOutlineRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(renderer, &rect);
	}

	void renderHorizontalLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
	}

	void renderVerticalDottedLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2, int interval)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		for (int i = pos1.y; i < pos2.y; i += interval)
		{
			SDL_RenderDrawPoint(renderer, pos1.x, i);
		}
	}


	//Rendering functions
	void renderInViewport(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *viewportRect)
	{
		SDL_Rect oldViewport;
		SDL_RenderGetViewport(renderer, &oldViewport);

		SDL_RenderSetViewport(renderer, viewportRect);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		SDL_RenderSetViewport(renderer, &oldViewport);
	}


	//Loading things
	SDL_Texture *loadTexture(SDL_Renderer *renderer, char *filePath)
	{
		if (renderer == NULL)
		{
			printf("loadTexture() failed for %s, renderer was NULL\n", filePath);
			return NULL;
		}
		SDL_Texture *newTexture = NULL;

		//Load the image
		SDL_Surface *loadedSurface = IMG_Load(filePath);
		if (loadedSurface == NULL)
		{
			printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		//Create a texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to create texture from %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		SDL_FreeSurface(loadedSurface);
		return newTexture;
	}

	SDL_Surface *loadSurface(SDL_Surface *screenSurface, char *filePath)
	{
		if (screenSurface == NULL)
		{
			printf("loadSurface() failed for %s, screenSurface was NULL\n", filePath);
			return NULL;
		}
		SDL_Surface *optimizedSurface = NULL;

		//Load the image
		SDL_Surface *loadedSurface = IMG_Load(filePath);
		if (loadedSurface == NULL)
		{
			printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		//Optimize the loaded image to the correct format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Failed to optimize image %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		return optimizedSurface;
	}
}