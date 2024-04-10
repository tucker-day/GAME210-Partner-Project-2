#include "EventHandler.h"
#include <stdio.h>
#include <string.h>

bool EventHandler::events[];

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::Update()
{
	bool success = true;

	SDL_Event currEvents;

	while(	SDL_PollEvent(&currEvents))
	{
		switch (currEvents.key.keysym.sym)
		{
		case SDLK_w:
		{
			SetButton(GameEvents::W_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_s:
		{
			SetButton(GameEvents::S_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_a:
		{
			SetButton(GameEvents::A_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_d:
		{
			SetButton(GameEvents::D_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		}
	}
	return success;
}

void EventHandler::SetButton(GameEvents eventNum, bool pressed)
{
	events[eventNum] = pressed;
}
