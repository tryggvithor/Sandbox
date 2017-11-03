#ifndef UTILS_H
#define UTILS_H

namespace utils
{
	struct Color { Uint8 r, g, b, a; };
	struct Position { int x, y; };

	//Primitives
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
		for (int i = pos1.y; i < pos2.y; i += interval)
		{
			SDL_RenderDrawPoint(renderer, pos1.x, i);
		}
	}

	//Rendering util functions
	void renderInViewport(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* viewportRect)
	{
		SDL_Rect oldViewport;
		SDL_RenderGetViewport(renderer, &oldViewport);

		SDL_RenderSetViewport(renderer, viewportRect);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		SDL_RenderSetViewport(renderer, &oldViewport);
	}
}


#endif // !UTILS_H
