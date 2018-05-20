#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include "utils.h"


class Texture
{
public:
	Texture(SDL_Renderer *renderer);
	~Texture();

	bool loadFromFile(utils::Color transparentColor, char *path);
	
	void setColor(utils::Color color);
	void setBlendMode(SDL_BlendMode blendMode);
	void setAlpha(Uint8 alpha);

	void renderAt(int x, int y, SDL_Rect *clip = NULL);
	void free();

private:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	int width, height;
};

#endif // !TEXTURE_H
