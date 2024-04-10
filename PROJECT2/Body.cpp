#include "Body.h"

void _Body::setOffset(int x, int y)
{
	offsetX = x;
	offsetY = y;

	moveTo(rect.x, rect.y);
}

inline void _Body::setOffsetX(int x) 
{ 
	offsetX = x; 

	moveTo(rect.x, rect.y);
}

inline void _Body::setOffsetY(int y) 
{ 
	offsetY = y; 

	moveTo(rect.x, rect.y);
}

void _Body::moveTo(int x, int y)
{
	rect.x = x + offsetX;
	rect.y = y + offsetY;
}

void _Body::moveTo(SDL_Rect r)
{
	rect.x = r.x + offsetX;
	rect.y = r.y + offsetY;
}

void _Body::setSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}
