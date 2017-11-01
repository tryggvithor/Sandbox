#ifndef GLOBALS_H
#define GLOBALS_H


class Globals
{
public:
	static int screenWidth;
	static int screenHeight;
	static bool hasQuit;
	static SDL_Renderer* renderer;
	static SDL_Window* window;
	static SDL_Texture* texture;
	static SDL_Surface* screenSurface;
	static char* hairmanFilePath;
};


#endif // !GLOBALS_H