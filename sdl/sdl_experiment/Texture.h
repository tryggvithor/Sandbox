#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include "utils.h"


class Texture
{
public:
	int width, height;

	Texture();
	~Texture();

	bool loadFromFile(SDL_Renderer *renderer, utils::Color transparentColor, char *path);
	
	void setColor(utils::Color color);
	void setBlendMode(SDL_BlendMode blendMode);
	void setAlpha(Uint8 alpha);

	void renderAt(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL);
	void free();

private:
	SDL_Texture *texture;
};

#endif // !TEXTURE_H
