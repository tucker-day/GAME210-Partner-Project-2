#pragma once

#include "SDL.h"
#include "Key.h"

enum GameEvents
{
	W_KEY,
	S_KEY,
	A_KEY,
	D_KEY,

	NUM_GAME_EVENTS
};

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	static bool Update();
	static void CleanState();
 
	static Key events[GameEvents::NUM_GAME_EVENTS];
private:

	static void SetButton(GameEvents eventNum, bool pressed);
};


