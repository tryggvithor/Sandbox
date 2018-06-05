#ifndef UTILS_H
#define UTILS_H


#include <SDL.h>
#include <SDL_image.h>

//Helpers

//Concatenate variable amount of char * into a new limited length malloced char *
char * _str_concat(char *first, ...);
#define str_concat(x, ...) _str_concat(x, __VA_ARGS__, NULL)

//Collision

//Rect to rect
extern bool rectCollision(SDL_Rect a, SDL_Rect b);

//Primitives

extern void renderFillRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect);
extern void renderOutlineRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect);
extern void renderHorizontalLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2);
extern void renderVerticalDottedLine(SDL_Renderer *renderer, SDL_Color color, SDL_Point pos1, SDL_Point pos2, int interval);

//Rendering functions

extern void renderInViewport(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *viewportRect);

//Loading things

extern SDL_Texture *loadTexture(SDL_Renderer *renderer, char *filePath);
extern SDL_Surface *loadSurface(SDL_Surface *screenSurface, char *filePath);



#endif // !UTILS_H
