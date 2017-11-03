#include <SDL.h>
#include "Utils.h"

void Utils::renderFillRect(SDL_Renderer* renderer, Utils::Color color, SDL_Rect rect)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Utils::renderOutlineRect(SDL_Renderer* renderer, Utils::Color color, SDL_Rect rect)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void Utils::drawHorizontalLine(SDL_Renderer* renderer, Utils::Color color, Utils::Position pos1, Utils::Position pos2)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}

void Utils::drawVerticalDottedLine(SDL_Renderer* renderer, Utils::Color color, Utils::Position pos1, Utils::Position pos2, int interval)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int i = pos1.y; i < pos2.y; i += interval)
	{
		SDL_RenderDrawPoint(renderer, pos1.x, i);
	}
}