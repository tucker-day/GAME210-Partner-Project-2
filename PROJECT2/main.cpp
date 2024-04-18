#pragma comment(lib, "XInput.lib")

#include "EventHandler.h"
#include "Graphics.h"
#include "GameplayManager.h"

bool GameRunning = true;

int main( int argc, char *argv[] )
{
	if (!Graphics::Init())
	{
		return false;
	}
	LoadManager::Init();
	EventHandler::Init();

	GameplayManager Game;

	// Main game loop
	while (GameRunning) 
	{
		Game.updateNextTime();

		// handle button events
		GameRunning = EventHandler::Update();
		Graphics::StartRender();
		
		Game.Update();
		Game.Render();

		SDL_Delay(Game.frameTimeLeft());

		// clean the event state
		EventHandler::CleanState();

		// apply the changes to the screen 
		Graphics::EndRender();
	}

	Graphics::Shutdown();
	LoadManager::Shutdown();
	EventHandler::Shutdown();

	//close off the SDL window
	SDL_Quit();

	return true;
}
