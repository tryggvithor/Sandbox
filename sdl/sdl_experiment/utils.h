#ifndef UTILS_H
#define UTILS_H


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

namespace utils
{
	//Helpers

	//Concatenate two char * into a new malloced char *
	static char * concat(const char *first, const char *second)
	{
		//Size of both char ptrs with a null terminator
		size_t size = (SDL_strlen(first) + SDL_strlen(second)) * sizeof(char) + 1;
		char *concatted = (char *)malloc(size);
		SDL_snprintf(concatted, size, "%s%s", first, second);
		return concatted;
	}


	//Primitives

	static void renderFillRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}

	static void renderOutlineRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(renderer, &rect);
	}

	static void renderHorizontalLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
	}

	static void renderVerticalDottedLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2, int interval)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		for (int i = pos1.y; i < pos2.y; i += interval)
		{
			SDL_RenderDrawPoint(renderer, pos1.x, i);
		}
	}


	//Rendering functions

	static void renderInViewport(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *viewportRect)
	{
		SDL_Rect oldViewport;
		SDL_RenderGetViewport(renderer, &oldViewport);

		SDL_RenderSetViewport(renderer, viewportRect);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		SDL_RenderSetViewport(renderer, &oldViewport);
	}


	//Loading things

	static SDL_Texture *loadTexture(SDL_Renderer *renderer, char *filePath)
	{
		if (renderer == NULL)
		{
			printf("loadTexture() failed for %s, renderer was NULL\n", filePath);
			return NULL;
		}

		SDL_Surface *loadedSurface = IMG_Load(filePath);
		if (loadedSurface == NULL)
		{
			printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		SDL_Texture *newTexture = NULL;
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to create texture from %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		SDL_FreeSurface(loadedSurface);
		return newTexture;
	}

	static SDL_Surface *loadSurface(SDL_Surface *screenSurface, char *filePath)
	{
		if (screenSurface == NULL)
		{
			printf("loadSurface() failed for %s, screenSurface was NULL\n", filePath);
			return NULL;
		}

		SDL_Surface *loadedSurface = IMG_Load(filePath);
		if (loadedSurface == NULL)
		{
			printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		//Optimize the loaded image to the correct format
		SDL_Surface *optimizedSurface = NULL;
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Failed to optimize image %s, error: %s\n", filePath, SDL_GetError());
			return NULL;
		}

		return optimizedSurface;
	}
}


#endif // !UTILS_H
