#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Texture.h"


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

bool Texture::loadFromFile(const char *path, SDL_Color *transparentColor)
{
	free();

	if (this->renderer == NULL)
	{
		printf("loadFromFile(%s) failed, renderer was NULL\n", path);
		return false;
	}

	SDL_Surface *loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("loadFromFile(%s) failed, error: %s\n", path, SDL_GetError());
		return false;
	}

	if (transparentColor != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, transparentColor->r, transparentColor->g, transparentColor->b));
	}

	this->texture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
	if (this->texture == NULL)
	{
		printf("loadFromFile(%s) failed, error: %s\n", path, SDL_GetError());
		return false;
	}

	this->width = loadedSurface->w;
	this->height = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);

	return true;
}

#ifdef _SDL_TTF_H
bool Texture::loadFromRenderedText(const char *text, TTF_Font *font, SDL_Color color)
{
	free();

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
	if (textSurface == NULL)
	{
		printf("loadFromRendereText(%s) failed, error: %s\n", text, TTF_GetError());
		return false;
	}

	this->texture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
	if (this->texture == NULL)
	{
		printf("loadFromRendereText(%s) failed, error: %s\n", text, SDL_GetError());
		return false;
	}

	this->width = textSurface->w;
	this->height = textSurface->h;
	SDL_FreeSurface(textSurface);

	return true;
}
#endif


void Texture::setColor(SDL_Color color)
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


void Texture::renderAt(int x, int y, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = {x, y, this->width, this->height};
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(this->renderer, this->texture, clip, &renderQuad, angle, center, flip);
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
