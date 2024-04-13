#pragma once

#include "GraphicsData.h"

class _Animator
{
public:
	_Animator(int f);
	~_Animator() {};

	void play(const char* key, bool override = false);
	void update();

	unsigned int getFrame() { return frame; };

private:
	_Anim* currentAnim;
	unsigned int frame;
	unsigned int frameRateTrack;
	unsigned int repeatTrack;
};