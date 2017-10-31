#ifndef GLOBALS_H
#define GLOBALS_H


class Globals
{
public:
	enum ArrowKeySurface
	{
		DEFAULT,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		COUNT
	};

	static int screenWidth;
	static int screenHeight;
	static bool hasQuit;
	static SDL_Renderer* renderer;
	static SDL_Window* window;
	static SDL_Texture* texture;
	static SDL_Surface* screenSurface;
	static SDL_Surface* currentSurface;
	static char* hairmanFilePath;
	static char* arrowKeyFilePaths[];
	static SDL_Surface* arrowKeySurfaces[];
};


#endif // !GLOBALS_H