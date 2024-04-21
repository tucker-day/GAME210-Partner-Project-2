#pragma once

#include "SDL.h"

// an sdl texture stored with its width and height
struct _Texture
{
	SDL_Texture* texture;
	int width, height;
};

// a texture stored with needed sprite data
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

// a struct of numbers used for animation
struct _Anim
{
	_Anim(const char* k, int sf, int ef, int fr, int r) : key(k), startFrame(sf), endFrame(ef), frameDelay(fr), repeat(r) {};
	const char* key;
	int startFrame, endFrame, frameDelay, repeat;
};