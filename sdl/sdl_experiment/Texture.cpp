#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Texture.h"
#include "utils.h"

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

bool Texture::loadFromFile(SDL_Renderer *renderer, utils::Color transparentColor, char *path)
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

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, transparentColor.r, transparentColor.g, transparentColor.b));
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


void Texture::setColor(utils::Color color)
{
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

void Texture::setBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(texture, blendMode);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}


void Texture::renderAt(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
	SDL_Rect renderQuad = {x, y, width, height};
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
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