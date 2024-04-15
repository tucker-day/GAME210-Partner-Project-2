#include "Body.h"

#include "Graphics.h"

bool _Body::checkCollision(_Body other)
{
	bool hor = false;
	bool vert = false;

	// get the left most shape and check if they are colliding on the horizontal axis
	if (rect.x < other.rect.x)
	{
		hor = (other.rect.x < rect.x + rect.w);
	}
	else
	{
		hor = (rect.x < other.rect.x + other.rect.w);
	}

	// get the highest shape and check if colliding on vertical axis
	if (rect.y < other.rect.y)
	{
		vert = (other.rect.y < rect.y + rect.h);
	}
	else
	{
		vert = (rect.y < other.rect.y + other.rect.h);
	}

	// return true if both are true
	return hor && vert;
}

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

void _Body::render(bool followCamera)
{
	Graphics::RenderRect(rect, followCamera);
}
