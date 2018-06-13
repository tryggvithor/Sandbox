#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>

typedef struct Circle
{
	double x, y;
	double r;
} Circle;

//Helpers

//Concatenate variable amount of char * ending with a NULL into a new limited length malloced char *
char * _str_concat(char *first, ...);

//Concatenate variable amount of char * into a new limited length malloced char *
#define str_concat(x, ...) _str_concat(x, __VA_ARGS__, NULL)

//Distance squared between two points
extern double dist_sq(double x1, double y1, double x2, double y2);


//Collision

//Rect to rect 
extern bool rect_collision(SDL_Rect a, SDL_Rect b);

//Rect array to rect array
extern bool rect_arrays_collision(SDL_Rect *a, SDL_Rect *b, int asize, int bsize);

//Circle to circle
extern bool circle_collision(Circle &a, Circle &b);

//Circle to rect
extern bool circle_rect_collision(Circle &a, SDL_Rect &b);


//Primitives

extern void render_fill_rect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect);
extern void render_outline_rect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect);
extern void render_horizontal_line(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2);
extern void render_vertical_dotted_line(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2, int interval);


//Rendering functions

extern void render_in_viewport(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *viewportRect);


//Loading things

extern SDL_Texture *load_texture(SDL_Renderer *renderer, char *filePath);
extern SDL_Surface *load_surface(SDL_Surface *screenSurface, char *filePath);


#endif // !UTILS_H
