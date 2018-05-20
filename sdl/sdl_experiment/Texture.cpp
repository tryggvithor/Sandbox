#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Texture.h"
#include "utils.h"

Texture::Texture(SDL_Renderer *renderer)
{
	this->renderer = renderer;
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(utils::Color transparentColor, char *path)
{
	free();

	if (this->renderer == NULL)
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
	newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
	if (newTexture == NULL)
	{
		return false;
	}

	//Create a texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("loadFromFile(%s) failed, error: %s\n", path, SDL_GetError());
		return false;
	}

	this->width = loadedSurface->w;
	this->height = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);

	this->texture = newTexture;
	return this->texture != NULL;
}


void Texture::setColor(utils::Color color)
{
	SDL_SetTextureColorMod(this->texture, color.r, color.g, color.b);
}

void Texture::setBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(this->texture, blendMode);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(this->texture, alpha);
}


void Texture::renderAt(int x, int y, SDL_Rect *clip)
{
	SDL_Rect renderQuad = {x, y, this->width, this->height};
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(this->renderer, this->texture, clip, &renderQuad);
}

void Texture::free()
{
	if (this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
		this->width = 0;
		this->height = 0;
	}
}