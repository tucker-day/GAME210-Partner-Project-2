#include "GameplayManager.h"

#include "EventHandler.h"

void GameplayManager::Init()
{
	LoadManager::loadSprite("knight", "knightSheet.bmp", 120, 80);
	LoadManager::loadSprite("error", "error.bmp");

	LoadManager::createAnimation("knight_walk", 0, 9, 3);
	LoadManager::createAnimation("test", 0, 40);

	player = objects.createSprite(50, 50, 0, "knight");
	player->body.setOffset(48, 42);
	player->body.setSize(26, 40);
	player->play("knight_walk");

	test = objects.createSprite(200, 200, 0, "error");
}

void GameplayManager::Update()
{	
	if (EventHandler::events[W_KEY].held) {
		player->transform.y -= 2;
	}
	if (EventHandler::events[S_KEY].held) {
		player->transform.y += 2;
	}
	if (EventHandler::events[D_KEY].held) {
		player->transform.x += 2;
	}
	if (EventHandler::events[A_KEY].held) {
		player->transform.x -= 2;
	}

	test->transform.rot += 2;

	if (player->body.checkCollision(test->body))
	{
		player->play("test");
	}

	objects.updateAll();
}

void GameplayManager::Render()
{
	objects.renderAll();
}

void GameplayManager::updateNextTime()
{
	// CODE IS BASED OFF YASH'S SDL TEMPLATE
	nextTime = SDL_GetTicks() + 1000 / FRAME_RATE;
}

Uint32 GameplayManager::frameTimeLeft()
{
	// CODE IS BASED OFF YASH'S SDL TEMPLATE
	Uint32 now;

	now = SDL_GetTicks();
	if (nextTime <= now)
		return 0;
	else
		return nextTime - now;
}
