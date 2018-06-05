#ifndef TEXTURE_H
#define TEXTURE_H


#include <SDL.h>
#include <SDL_ttf.h>

class Texture
{
public:
	int width, height;

	Texture(SDL_Renderer *renderer);
	~Texture();

	bool load_from_file(const char *path, SDL_Color *transparentColor = NULL);
#ifdef _SDL_TTF_H
	bool load_from_rendered_text(const char *text, TTF_Font *font, SDL_Color color = {0x00, 0x00, 0x00, 0xFF});
#endif

	void set_color(SDL_Color color);
	void set_blend_mode(SDL_BlendMode blendMode);
	void set_alpha(Uint8 alpha);

	void render_at(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

private:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};


#endif // !TEXTURE_H
