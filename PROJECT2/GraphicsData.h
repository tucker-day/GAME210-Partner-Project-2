#pragma once

#include "SDL.h"

// an sdl texture stored with its width and height
struct _Texture
{
	SDL_Texture* texture;
	int width, height;
};

struct _Sprite
{
	_Sprite(const char* k, _Texture t, int fw, int fh) : key(k), texture(t), frameWidth(fw), frameHeight(fh)
	{
		numSpritesX = floor((float)t.width / fw);
		numSpritesY = floor((float)t.height / fh);
	};

	_Texture texture;
	int frameWidth, frameHeight, numSpritesX, numSpritesY;
	const char* key;
};

struct _Anim
{
	int startFrame, endFrame, frameRate, repeat;
	const char* key;
};