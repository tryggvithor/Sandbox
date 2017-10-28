#include <SDL.h>
#include "Globals.h"


int Globals::screenWidth = 1280;
int Globals::screenHeight = 720;
bool Globals::hasQuit = false;
SDL_Window* Globals::window = NULL;
SDL_Surface* Globals::screenSurface = NULL;
SDL_Surface* Globals::currentSurface = NULL;

char* Globals::arrowKeyFilePaths[] =
{
	"images/default.bmp",
	"images/up.bmp",
	"images/down.bmp",
	"images/left.bmp",
	"images/right.bmp"
};

SDL_Surface* Globals::arrowKeySurfaces[ArrowKeySurface::COUNT];