#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>


class Texture
{
public:
	int width, height;

	Texture();
	~Texture();

	bool loadFromFile(SDL_Renderer *renderer, char *path);
	void renderAt(SDL_Renderer *renderer, int x, int y);
	void free();

private:
	SDL_Texture *texture;
};

#endif // !TEXTURE_H
