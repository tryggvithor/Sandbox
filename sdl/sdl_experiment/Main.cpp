#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Globals.h"


struct Color
{
	Uint8 r, g, b, a;
};

struct Position
{
	int x, y;
};


bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(char* filePath);
SDL_Surface* loadSurface(char* filePath);
void renderFillRect(SDL_Renderer* renderer, Color color, SDL_Rect rect);
void renderOutlineRect(SDL_Renderer* renderer, Color color, SDL_Rect rect);
void drawHorizontalLine(SDL_Renderer* renderer, Color color, Position pos1, Position pos2);
void drawVerticalDottedLine(SDL_Renderer* renderer, Color color, Position pos1, Position pos2, int interval);



int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initalize\n");
		return 0;
	}
	if (!loadMedia())
	{
		printf("Failed to load media\n");
		return 0;
	}

	SDL_Event e;

	//Temporary things
	SDL_Rect fillRect = {Globals::screenWidth / 4, Globals::screenHeight / 4, Globals::screenWidth / 2, Globals::screenHeight / 2};
	Color color_red = {0xff, 0x00, 0x00, 0xff};

	SDL_Rect outlineRect = {Globals::screenWidth / 6, Globals::screenHeight / 6, Globals::screenWidth * 2 / 3, Globals::screenHeight * 2 / 3};
	Color color_green = {0x00, 0xff, 0x00, 0xff};

	Position pos_hori1 = {0, Globals::screenHeight / 2};
	Position pos_hori2 = {Globals::screenWidth, Globals::screenHeight / 2};
	Color color_blue = {0x00, 0x00, 0xff, 0xff};

	Position pos_vert1 = {Globals::screenWidth / 2, 0};
	Position pos_vert2 = {Globals::screenWidth, Globals::screenHeight};
	Color color_yellow = {0xff, 0xff, 0x00, 0xff};


	while (!Globals::hasQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				Globals::hasQuit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				
			}
		}

		SDL_SetRenderDrawColor(Globals::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Globals::renderer);

		renderFillRect(Globals::renderer, color_red, fillRect);
		renderOutlineRect(Globals::renderer, color_green, outlineRect);
		drawHorizontalLine(Globals::renderer, color_blue, pos_hori1, pos_hori2);
		drawVerticalDottedLine(Globals::renderer, color_yellow, pos_vert1, pos_vert2, 4);

		SDL_RenderPresent(Globals::renderer);
	}

	close();
	return 0;
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_INIT failed, error: %s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed to initialize, error: %s\n", IMG_GetError());
		return false;
	}

	Globals::window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN);
	if (Globals::window == NULL)
	{
		printf("SDL_CreateWindow failed, error: %s\n", SDL_GetError());
		return false;
	}

	Globals::renderer = SDL_CreateRenderer(Globals::window, -1, SDL_RENDERER_ACCELERATED);
	if (Globals::renderer == NULL)
	{
		printf("SDL_CreateRenderer failed, error: %s\n", SDL_GetError());
		return false;
	}

	Globals::screenSurface = SDL_GetWindowSurface(Globals::window);

	return true;
}

bool loadMedia()
{
	Globals::texture = loadTexture(Globals::hairmanFilePath);
	if (Globals::texture == NULL)
	{
		printf("Failed to load texture image %s\n", Globals::hairmanFilePath);
		return false;
	}

	return true;
}

SDL_Texture* loadTexture(char* filePath)
{
	if (Globals::renderer == NULL)
	{
		printf("loadTexture() failed for %s, global renderer was NULL\n", filePath);
		return NULL;
	}
	SDL_Texture* newTexture = NULL;

	//Load the image
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	if (loadedSurface == NULL)
	{
		printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	//Create a texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(Globals::renderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("Failed to create texture from %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

SDL_Surface* loadSurface(char* filePath)
{
	if (Globals::screenSurface == NULL)
	{
		printf("loadSurface() failed for %s, global screenSurface was NULL\n", filePath);
		return NULL;
	}
	SDL_Surface* optimizedSurface = NULL;

	//Load the image
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	if (loadedSurface == NULL)
	{
		printf("Failed to load image %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	//Optimize the loaded image to the correct format
	optimizedSurface = SDL_ConvertSurface(loadedSurface, Globals::screenSurface->format, NULL);
	if (optimizedSurface == NULL)
	{
		printf("Failed to optimize image %s, error: %s\n", filePath, SDL_GetError());
		return NULL;
	}

	return optimizedSurface;
}

void renderFillRect(SDL_Renderer* renderer, Color color, SDL_Rect rect)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void renderOutlineRect(SDL_Renderer* renderer, Color color, SDL_Rect rect)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void drawHorizontalLine(SDL_Renderer* renderer, Color color, Position pos1, Position pos2)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}

void drawVerticalDottedLine(SDL_Renderer* renderer, Color color, Position pos1, Position pos2, int interval)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int i = pos1.y; i < pos2.y; i+=interval)
	{
		SDL_RenderDrawPoint(renderer, pos1.x, i);
	}
}


void close()
{
	//Textures
	SDL_DestroyTexture(Globals::texture);
	Globals::texture = NULL;

	//Window
	SDL_DestroyRenderer(Globals::renderer);
	SDL_DestroyWindow(Globals::window);
	Globals::renderer = NULL;
	Globals::window = NULL;

	//SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

