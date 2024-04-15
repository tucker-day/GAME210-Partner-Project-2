#pragma once

#include <string>

#include "SDL.h"

using namespace std;

struct Colour
{
	int r;
	int g;
	int b;
};

struct Vec2D
{
	float x;
	float y;
};

// sdl rect with the addition of rotation. passable as a sdl_rect for functions
struct _Transform : public SDL_Rect
{
	_Transform(int nx, int ny, int nw, int nh, double nr)
	{
		x = nx;
		y = ny;
		w = nw;
		h = nh;
		rot = nr;
	}

	// easily turn an sdl rect into a full transform
	_Transform(SDL_Rect s, double r) 
	{
		x = s.x;
		y = s.y;
		w = s.w;
		h = s.h;
		rot = r;
	};
	
	double rot;
};