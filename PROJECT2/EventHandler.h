#pragma once

#include "SDL.h"
#include "Key.h"
#include "Controller.h"

enum GameEvents
{
	W_KEY,
	S_KEY,
	A_KEY,
	D_KEY,
	R_KEY,
	ESC_KEY,
	F11_KEY,

	NUM_GAME_EVENTS
};

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	static void Init();
	static void Shutdown();

	static bool Update();
	static void CleanState();
 
	static Key events[GameEvents::NUM_GAME_EVENTS];
	static Controller* controller;

private:
	static void SetButton(GameEvents eventNum, bool pressed);
};


