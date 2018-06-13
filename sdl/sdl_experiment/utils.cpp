#include <SDL_image.h>
#include <stdio.h>
#include "utils.h"

//Helpers

char * _str_concat(char *first, ...)
{
	va_list args;
	va_start(args, first);

	char * str = first;
	char * concatted = (char*)malloc(256);
	char * ptr = concatted;
	size_t length;
	while (str != NULL)
	{
		length = SDL_strlen(str);
		SDL_memcpy(ptr, str, length);

		ptr += length;
		str = va_arg(args, char*);
	} 
	*ptr = '\0';

	va_end(args);

	return concatted;
}


double dist_sq(double x1, double y1, double x2, double y2) 
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	return dx*dx + dy*dy;
}



//Collision

extern bool rect_collision(SDL_Rect a, SDL_Rect b)
{
	return SDL_HasIntersection(&a, &b);
}

extern bool rect_arrays_collision(SDL_Rect *a, SDL_Rect *b, int asize, int bsize)
{
	for (int i = 0; i < asize; i++)
	{
		for (int j = 0; j < bsize; j++)
		{
			if (SDL_HasIntersection(&a[i], &b[j]))
			{
				return true;
			}
		}
	}
	return false;
}

extern bool circle_collision(Circle &a, Circle &b)
{
	double totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	//Return if the distance between the centers of the circles is less than the sum of their radii
	return dist_sq(a.x, a.y, b.x, b.y) < totalRadiusSquared;
}

extern bool circle_rect_collision(Circle &a, SDL_Rect &b)
{
	//Closest point on collision box
	double cX, cY;

	//Find closest x offset
	if (a.x < b.x) cX = b.x;
	else if (a.x > b.x + b.w) cX = b.x + b.w; 
	else cX = a.x; 

	//Find closest y offset
	if (a.y < b.y) cY = b.y; 
	else if (a.y > b.y + b.h) cY = b.y + b.h;
	else cY = a.y; 

	//Return if the closest point is inside the circle
	return dist_sq(a.x, a.y, cX, cY) < a.r * a.r;
}


//Primitives

extern void render_fill_rect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

extern void render_outline_rect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

extern void render_horizontal_line(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}

extern void render_vertical_dotted_line(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2, int interval)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int i = pos1.y; i < pos2.y; i += interval)
	{
		SDL_RenderDrawPoint(renderer, pos1.x, i);
	}
}


//Rendering functions

extern void render_in_viewport(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *viewportRect)
{
	SDL_Rect oldViewport;
	SDL_RenderGetViewport(renderer, &oldViewport);

	SDL_RenderSetViewport(renderer, viewportRect);
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_RenderSetViewport(renderer, &oldViewport);
}


//Loading things

extern SDL_Texture *load_texture(SDL_Renderer *renderer, char *filePath)
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

extern SDL_Surface *load_surface(SDL_Surface *screenSurface, char *filePath)
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
