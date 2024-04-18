#include "EventHandler.h"

Key EventHandler::events[];
Controller* EventHandler::controller;

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::Init()
{
	controller = new Controller();
}

void EventHandler::Shutdown()
{
	delete controller;
}

bool EventHandler::Update()
{
	controller->Update();

	bool success = true;

	SDL_Event currEvents;

	while(	SDL_PollEvent(&currEvents))
	{
		switch (currEvents.key.keysym.sym)
		{
			case SDLK_w: {
				SetButton(GameEvents::W_KEY, currEvents.key.type == SDL_KEYDOWN);
				break;
			}
			case SDLK_s: {
				SetButton(GameEvents::S_KEY, currEvents.key.type == SDL_KEYDOWN);
				break;
			}
			case SDLK_a: {
				SetButton(GameEvents::A_KEY, currEvents.key.type == SDL_KEYDOWN);
				break;
			}
			case SDLK_d: {
				SetButton(GameEvents::D_KEY, currEvents.key.type == SDL_KEYDOWN);
				break;
			}
			case SDLK_r: {
				SetButton(GameEvents::R_KEY, currEvents.key.type == SDL_KEYDOWN);
				break;
			}
			case SDLK_F11: {
				SetButton(GameEvents::F11_KEY, currEvents.key.type == SDL_KEYDOWN);
				break;
			}
			case SDLK_ESCAPE: {
				SetButton(GameEvents::ESC_KEY, currEvents.key.type == SDL_KEYDOWN);
				break;
			}
		}
	}

	// check for quit event
	if (currEvents.type == SDL_QUIT || events[ESC_KEY].pressed)
	{
		success = false;
	}

	return success;
}

void EventHandler::CleanState()
{
	for (int i = 0; i < NUM_GAME_EVENTS; i++)
	{
		events[i].pressed = false;
		events[i].raised = false;
	}
}

void EventHandler::SetButton(GameEvents eventNum, bool pressed)
{
	// set bools based on input
	if (pressed)
	{
		events[eventNum].pressed = true;
		events[eventNum].held = true;
	}
	else
	{
		events[eventNum].held = false;
		events[eventNum].raised = true;
	}
}
