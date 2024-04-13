#include "Animator.h"

#include "LoadManager.h"

_Animator::_Animator(int f)
	: frame(f), frameRateTrack(0), repeatTrack(0), currentAnim(nullptr) {}

void _Animator::play(const char* key)
{
	// get the new animation based on the key and reset trackers
	currentAnim = LoadManager::getAnim(key);

	if (currentAnim != nullptr)
	{
		frame = currentAnim->startFrame;
		frameRateTrack = 0;
		repeatTrack = 0;
	}
}

void _Animator::update()
{
	if (currentAnim != nullptr)
	{
		// check frame rate track to see if it should update
		if (frameRateTrack >= currentAnim->frameDelay)
		{
			// reset frame rate track
			frameRateTrack = 0;

			// check if the final frame of the animation was played
			if (frame >= currentAnim->endFrame)
			{
				// check if it can repeat again
				if (repeatTrack < currentAnim->repeat || currentAnim->repeat < 0)
				{
					// if it can repeat, set frame back to the start and update repeat track
					frame = currentAnim->startFrame;
					repeatTrack++;
				}
			}
			else
			{
				// if not final frame, move to the next frame
				frame++;
			}
		}
		else
		{
			// if not updating frame, increase frame rate track
			frameRateTrack++;
		}
	}
}
