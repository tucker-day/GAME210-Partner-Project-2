#pragma once

#include <vector>

#include "Graphics.h"

using namespace std;

class LoadManager
{
public:
	static void Init();
	static void Shutdown();

	// loads a sprite into the game. if sprite width and sprite height are is less than 0, 
	// the entire sprite is treated as a single frame. if sprite height is less than 0, it
	// uses the same value as sprite width
	static void loadSprite(const char* key, const char* file, int spriteWidth = -1, int spriteHeight = -1);

	// creates a new animation. if anim will repeat forever, repeat must be -1. frame delay
	// is the number of frames between the sprite changing. a frame delay of 0 would be
	// updating every frame, a delay of 1 would be every 2nd frame, a delay of 2 would be
	// every 3rd frame, and so on.
	static void createAnimation(const char* key, int startFrame, int endFrame, int frameDelay = 0, int repeat = -1);

	// returns a pointer to the sprite object
	static _Sprite* getSprite(const char* key);

	// checks if sprite with key exists
	static bool spriteKeyExists(const char* key);

	// returns a pointer to the anim object
	static _Anim* getAnim(const char* key);

private:
	// declare pointers to vectors
	static vector<_Sprite*> *sprites;
	static vector<_Anim*> *animations;
};