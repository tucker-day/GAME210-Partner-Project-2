#pragma once

#include <vector>

#include "Graphics.h"
#include "GraphicsData.h"

using namespace std;

class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	// loads a sprite into the game. if sprite width and sprite height are is less than 0, 
	// the entire sprite is treated as a single frame. if sprite height is less than 0, it
	// uses the same value as sprite width
	void loadSprite(const char* key, const char* file, int spriteWidth = -1, int spriteHeight = -1);

	// returns a pointer to the sprite object
	_Sprite* getSprite(const char* key);

private:
	// declare pointers to vectors
	vector<_Sprite*> *sprites;
};