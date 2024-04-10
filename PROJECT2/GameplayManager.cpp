#include "GameplayManager.h"

#include "EventHandler.h"

void GameplayManager::Init()
{
	objects.loadManager.loadSprite("knight", "knightSheet.bmp", 120, 80);
	objects.loadManager.loadSprite("error", "error.bmp");

	player = objects.createSprite(50, 50, 0, "knight");
	player->body.setOffset(48, 42);
	player->body.setSize(26, 40);

	test = objects.createSprite(200, 200, 0, "error");
}

void GameplayManager::Update()
{
	player->changeFrame();
	
	if (EventHandler::events[W_PRESSED]) {
		player->transform.y -= 2;
	}
	if (EventHandler::events[S_PRESSED]) {
		player->transform.y += 2;
	}
	if (EventHandler::events[D_PRESSED]) {
		player->transform.x += 2;
	}
	if (EventHandler::events[A_PRESSED]) {
		player->transform.x -= 2;
	}

	test->transform.rot += 2;

	objects.updateAll();
}

void GameplayManager::Render()
{
	objects.renderAll();
}