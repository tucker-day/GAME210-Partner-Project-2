#pragma once

#include "SDL.h"

class _Body
{
public:
	_Body(SDL_Rect t) : rect(t) {};
	~_Body() {};

	SDL_Rect getRect() { return rect; };

	// sets an offset for the body. for example, if you tell a body with an offset
	// of 10x 20y to move to 10x 10y, the body will be placed at 20x 30y
	void setOffset(int x, int y);
	void setOffsetX(int x);
	void setOffsetY(int y);

	// moves to a position with the offset applied
	void moveTo(int x, int y);
	void moveTo(SDL_Rect r);

	// sets the width and height of the body
	void setSize(int w, int h);

private:
	SDL_Rect rect;
	int offsetX = 0, offsetY = 0;
};