#include <SDL.h>
#include "Button.h" 

Button::Button(Texture *texture, SDL_Rect *textureClips, int width, int height)
{
	this->pos.x = 0;
	this->pos.y = 0;
	this->width = width;
	this->height = height;
	this->currentState = this->ButtonStates::MOUSE_OUT;
	this->texture = texture;
	this->textureClips = textureClips;
}

Button::~Button()
{

}

void Button::handleEvent(SDL_Event *e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type || SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = false;
		//Check if the mouse is within the button's boundaries
		if (x > this->pos.x && x < this->pos.x + this->width &&
			y > this->pos.y && y < this->pos.y + this->height)
		{
			inside = true;
		}

		if (!inside)
		{
			this->currentState = this->ButtonStates::MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				this->currentState = this->ButtonStates::MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->currentState = this->ButtonStates::MOUSE_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				this->currentState = this->ButtonStates::MOUSE_UP;
				break;
			}
		}
	}
}

void Button::render()
{
	this->texture->renderAt(this->pos.x, this->pos.y, &this->textureClips[this->currentState]);
}