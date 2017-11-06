#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Texture.h"

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(SDL_Renderer *renderer, char *path)
{
	free();

	if (renderer == NULL)
	{
		printf("loadFromFile(%s) failed, renderer was NULL\n", path);
		return false;
	}
	SDL_Texture *newTexture = NULL;

	//Load the image
	SDL_Surface *loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("loadFromFile(%s) failed, error: %s\n", path, SDL_GetError());
		return false;
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xff, 0xff));
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL)
	{
		return false;
	}

	//Create a texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("loadFromFile(%s) failed, error: %s\n", path, SDL_GetError());
		return false;
	}

	width = loadedSurface->w;
	height = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);

	texture = newTexture;
	return texture != NULL;
}

void Texture::renderAt(SDL_Renderer *renderer, int x, int y)
{
	SDL_Rect renderQuad = {x, y, width, height};
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}