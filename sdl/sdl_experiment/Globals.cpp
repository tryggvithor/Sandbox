#include <SDL.h>
#include "Globals.h"


int Globals::screenWidth = 1280;
int Globals::screenHeight = 720;
bool Globals::hasQuit = false;
SDL_Renderer* Globals::renderer = NULL;
SDL_Window* Globals::window = NULL;
SDL_Texture* Globals::texture = NULL;
SDL_Surface* Globals::screenSurface = NULL;
SDL_Surface* Globals::currentSurface = NULL;

char* Globals::hairmanFilePath = "images/hairman.png";
char* Globals::arrowKeyFilePaths[] =
{
	"images/default.png",
	"images/up.png",
	"images/down.png",
	"images/left.png",
	"images/right.png"
};

SDL_Surface* Globals::arrowKeySurfaces[ArrowKeySurface::COUNT];