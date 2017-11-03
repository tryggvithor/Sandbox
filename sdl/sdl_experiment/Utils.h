#ifndef UTILS_H
#define UTILS_H

class Utils
{
public: 
	struct Color { Uint8 r, g, b, a; };
	struct Position { int x, y;	};

	void renderFillRect(SDL_Renderer* renderer, Color color, SDL_Rect rect);
	void renderOutlineRect(SDL_Renderer* renderer, Color color, SDL_Rect rect);
	void drawHorizontalLine(SDL_Renderer* renderer, Color color, Position pos1, Position pos2);
	void drawVerticalDottedLine(SDL_Renderer* renderer, Color color, Position pos1, Position pos2, int interval);

	void renderInViewport(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* viewportRect);
};


#endif // !UTILS_H
