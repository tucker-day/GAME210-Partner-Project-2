#include "GameplayManager.h"

#include "EventHandler.h"

// load all sprite assets here
void GameplayManager::Preload()
{
	LoadManager::loadSprite("knight", "knightSheet.bmp", 120, 80);
	LoadManager::loadSprite("error", "error.bmp");

	LoadManager::createAnimation("knight_walk", 0, 9, 3);
	LoadManager::createAnimation("test", 0, 40);
}

void GameplayManager::Init()
{
	player = objects.createSprite(50, 50, 0, "knight");
	player->body.setOffset(48, 42);
	player->body.setSize(26, 40);
	player->play("knight_walk");

	test = objects.createSprite(200, 200, 0, "error");

	uiTest = objects.createSprite(25, 25, 0, "error");
	uiTest->followCamera = true;

	textTest = objects.createText("Test", 0, 0, 100, 255, 0, 255);

	uiText = objects.createText("F11 to go fullscreen", Graphics::WINDOW_WIDTH / 2, 50, 50, 255, 0, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 0);
}

void GameplayManager::Restart()
{
	objects.deleteAllObjects();
	objects.deleteAllText();

	Init();

	restartScene = false;
}

void GameplayManager::Update()
{	
	if (restartScene) { Restart(); }

	if (EventHandler::events[W_KEY].held || EventHandler::controller->GetStickLYValue() > 0.2) {
		player->transform.y -= 2;
	}
	if (EventHandler::events[S_KEY].held || EventHandler::controller->GetStickLYValue() < -0.2) {
		player->transform.y += 2;
	}
	if (EventHandler::events[D_KEY].held || EventHandler::controller->GetStickLXValue() > 0.2) {
		player->transform.x += 2;
	}
	if (EventHandler::events[A_KEY].held || EventHandler::controller->GetStickLXValue() < -0.2) {
		player->transform.x -= 2;
	}

	if (EventHandler::events[W_KEY].pressed || EventHandler::controller->IsAPressed()) {
		textTest->setColour(255, 255, 255);
	}
	if (EventHandler::events[A_KEY].pressed) {
		textTest->setText("It did the thing");
	}
	if (EventHandler::events[D_KEY].pressed) {
		textTest->setFontSize(50);
	}

	if (EventHandler::events[F11_KEY].pressed) {
		Graphics::ToggleFullscreen();
	}

	if (EventHandler::events[R_KEY].pressed) {
		restartScene = true;
	}

	test->transform.rot += 2;

	if (player->body.checkCollision(test->body))
	{
		player->play("test");
	}

	objects.updateAll();

	Graphics::MoveCameraTo(player->body.getRect());
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
