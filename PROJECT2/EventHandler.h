#pragma once

#include "SDL.h"
#include "Key.h"
#include "Controller.h"

enum GameEvents
{
	UP_KEY,
	DOWN_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	R_KEY,
	Z_KEY,
	X_KEY,
	C_KEY,
	F11_KEY,
	SPACE_KEY,
	ESC_KEY,

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


