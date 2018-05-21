#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "utils.h"


class Texture
{
public:
	int width, height;

	Texture(SDL_Renderer *renderer);
	~Texture();

	bool loadFromFile(char *path, SDL_Color *transparentColor = NULL);
#ifdef _SDL_TTF_H
	bool loadFromRenderedText(char *text, TTF_Font *font, SDL_Color color = {0x00, 0x00, 0x00, 0x00});
#endif

	void setColor(SDL_Color color);
	void setBlendMode(SDL_BlendMode blendMode);
	void setAlpha(Uint8 alpha);

	void renderAt(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

private:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

#endif // !TEXTURE_H
