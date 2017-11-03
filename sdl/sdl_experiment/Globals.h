#ifndef GLOBALS_H
#define GLOBALS_H


namespace globals
{
	int screenWidth = 1280;
	int screenHeight = 729;
	bool hasQuit = false;
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	SDL_Texture* texture = NULL;
	SDL_Surface* screenSurface = NULL;
	char* hairmanFilePath = "images/hairman.png";
};


#endif // !GLOBALS_H