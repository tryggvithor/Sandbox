#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include "utils.h"


class Texture
{
public:
	int width, height;
	Texture(SDL_Renderer *renderer);
	~Texture();

	bool loadFromFile(utils::Color transparentColor, char *path);
	
	void setColor(utils::Color color);
	void setBlendMode(SDL_BlendMode blendMode);
	void setAlpha(Uint8 alpha);

	void renderAt(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

private:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

#endif // !TEXTURE_H
