#include "GameplayManager.h"

#include "EventHandler.h"

#include <queue>

// load all sprite assets here
void GameplayManager::Preload()
{
	LoadManager::loadSprite("knight", "knightSheet.bmp", 40, 40);
	LoadManager::createAnimation("knight_walk", 0, 9, 4);
	LoadManager::createAnimation("knight_idle", 10, 19, 4);

	LoadManager::loadSprite("test", "nope.bmp");

	LoadManager::loadSprite("grass", "grass.bmp");

	LoadManager::loadSprite("saw", "saw.bmp");
	LoadManager::loadSprite("axe", "axe.bmp");

	LoadManager::loadSprite("sword", "sword.bmp", 192, 64);
	LoadManager::createAnimation("swing", 0, 5, 2, 0);

	LoadManager::loadSprite("sprint", "sprint.bmp", 64);
	LoadManager::loadSprite("sawIcon", "sawIcon.bmp", 64);
	LoadManager::loadSprite("swordIcon", "swordIcon.bmp", 64);
	LoadManager::loadSprite("axeIcon", "axeIcon.bmp", 64);

	LoadManager::createAnimation("onCooldown", 0, 0);
	LoadManager::createAnimation("canUse", 1, 1);

	LoadManager::loadSprite("flyEye", "flyingEye.bmp", 60, 50);
	LoadManager::createAnimation("flying", 0, 7, 5);

	LoadManager::loadSprite("goblin", "goblin.bmp", 50, 50);
	LoadManager::createAnimation("goblin_walk", 0, 7, 5);

	LoadManager::loadSprite("shroom", "shroom.bmp", 50, 50);
	LoadManager::createAnimation("shroom_walk", 0, 7, 5);

	LoadManager::loadSprite("skeleton", "skeleton.bmp", 50, 50);
	LoadManager::createAnimation("skeleton_walk", 0, 3, 5);
}

void GameplayManager::Init()
{
	// creating the grass
	for (int i = 0; i < NUM_GRASS; i++)
	{
		grass[i] = objects.createSprite(0, 0, 0, "grass");
		grass[i]->transform.x = grass[i]->transform.w * (i % NUM_GRASS_X);
		grass[i]->transform.y = grass[i]->transform.h * floor((float)i / (float)NUM_GRASS_X);
	}

	// creating the player
	player = objects.createSprite(Graphics::WINDOW_WIDTH / 2, Graphics::WINDOW_HEIGHT / 2, 0, "knight");
	player->body.setOffset(10, 3);
	player->body.setSize(20, 37);
	player->play("knight_walk");

	// setting the sprint ability stuff
	sprintIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "sprint", 1);
	sprintIcon->followCamera = true;

	Text* uiText = objects.createText("Space / R3", sprintIcon->transform.x + sprintIcon->transform.w / 2, sprintIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	sprintTimer = objects.createText("0", sprintIcon->transform.x + sprintIcon->transform.w / 2, sprintIcon->transform.y + sprintIcon->transform.h / 2, 30, 255, 255, 255, false);
	sprintTimer->setOrigin(0.5);
	sprintTimer->followCamera = true;

	sprintCooldown = 0;

	// setting the axe ability stuff
	axeIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94 * 2, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "axeIcon", 1);
	axeIcon->followCamera = true;

	uiText = objects.createText("C Key / RT", axeIcon->transform.x + axeIcon->transform.w / 2, axeIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	axeTimer = objects.createText("0", axeIcon->transform.x + axeIcon->transform.w / 2, axeIcon->transform.y + axeIcon->transform.h / 2, 30, 255, 255, 255, false);
	axeTimer->setOrigin(0.5);
	axeTimer->followCamera = true;

	axeCooldown = 0;

	axe = objects.createSprite(0, 0, 0, "axe", 0, false);

	// setting the saw ability stuff
	sawIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94 * 3, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "sawIcon", 1);
	sawIcon->followCamera = true;

	uiText = objects.createText("X Key / A Button", sawIcon->transform.x + sawIcon->transform.w / 2, sawIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	sawTimer = objects.createText("0", sawIcon->transform.x + sawIcon->transform.w / 2, sawIcon->transform.y + sawIcon->transform.h / 2, 30, 255, 255, 255, false);
	sawTimer->setOrigin(0.5);
	sawTimer->followCamera = true;

	sawCooldown = 0;

	for (int i = 0; i < NUM_SAWS; i++)
	{
		saws[i] = objects.createSprite(0, 0, 0, "saw", 0, false);
	}

	// setting the sword ability stuff
	swordIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94 * 4, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "swordIcon", 1);
	swordIcon->followCamera = true;

	uiText = objects.createText("Z Key / X Button", swordIcon->transform.x + swordIcon->transform.w / 2, swordIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	swordTimer = objects.createText("0", swordIcon->transform.x + swordIcon->transform.w / 2, swordIcon->transform.y + swordIcon->transform.h / 2, 30, 255, 255, 255, false);
	swordTimer->setOrigin(0.5);
	swordTimer->followCamera = true;

	swordCooldown = 0;

	sword = objects.createSprite(0, 0, 0, "sword", 0, false);

	// assorted controls
	uiText = objects.createText("Back or ESC to Quit", 20, Graphics::WINDOW_HEIGHT - 20, 15, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0, 1);

	uiText = objects.createText("F11 to go Fullscreen", 20, Graphics::WINDOW_HEIGHT - 40, 15, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0, 1);

	uiText = objects.createText("R to Restart", 20, Graphics::WINDOW_HEIGHT - 60, 15, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0, 1);

	uiText = objects.createText("Move with Arrow Keys, DPAD or Left Stick", 20, Graphics::WINDOW_HEIGHT - 80, 15, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0, 1);

	// health and score text
	health = 100;
	healthText = objects.createText("HP: 100", Graphics::WINDOW_WIDTH / 2, Graphics::WINDOW_HEIGHT - 60, 25, 255, 255, 255);
	healthText->followCamera = true;
	healthText->setOrigin(0.5, 1);

	score = 0;
	scoreText = objects.createText("SCORE: 0", Graphics::WINDOW_WIDTH / 2, Graphics::WINDOW_HEIGHT - 30, 25, 255, 255, 255);
	scoreText->followCamera = true;
	scoreText->setOrigin(0.5, 1);

	// set up enemy spawning
	spawnCooldown = INIT_ENEMY_SPAWN_SPEED;
}

void GameplayManager::Restart()
{
	objects.deleteAllObjects();
	objects.deleteAllText();

	enemies.clear();

	Init();

	restartScene = false;
	gameOver = false;
}

void GameplayManager::SystemControls()
{
	if (EventHandler::events[F11_KEY].pressed) {
		Graphics::ToggleFullscreen();
	}

	if (EventHandler::events[R_KEY].pressed) {
		restartScene = true;
	}
}

void GameplayManager::GameOver()
{
	gameOver = true;
	leaderboard.AddEntry(score);

	Text* temp = objects.createText("GAME OVER", 50, Graphics::WINDOW_HEIGHT / 2, 50, 255, 255, 255);
	temp->setOrigin(0, 1);
	temp->followCamera = true;

	char num[15];
	_itoa_s(score, num, 10);

	string text = "Final Score: ";
	text.append(num);
	
	temp = objects.createText(text.c_str(), 50, Graphics::WINDOW_HEIGHT / 2 - 1, 25, 255, 255, 255);
	temp->followCamera = true;

	temp = objects.createText("LEADERBOARD", Graphics::WINDOW_WIDTH - 50, Graphics::WINDOW_HEIGHT / 2 - 200, 25, 255, 255, 255);
	temp->setOrigin(1, 0);
	temp->followCamera = true;

	for (int i = 0; i < MAX_ENTRIES; i++)
	{
		_itoa_s(leaderboard.GetEntry(i), num, 10);

		temp = objects.createText(num, Graphics::WINDOW_WIDTH - 50, Graphics::WINDOW_HEIGHT / 2 - 200 + 30 * (i + 1), 25, 255, 255, 255);
		temp->setOrigin(1, 0);
		temp->followCamera = true;

		if (leaderboard.GetEntry(i) == score)
		{
			temp->setColour(255, 0, 0);
		}
	}

	leaderboard.Save();
}

bool GameplayManager::Update()
{
	try
	{
		SystemControls();

		if (restartScene) { Restart(); }
		
		if (!gameOver)
		{
			OnUpdate();
			objects.updateAll();
		}

		return true;
	}
	catch (...)
	{
		// if there's an exception, safely crash the game
		return false;
	}
}

bool GameplayManager::Render()
{
	try
	{
		objects.renderAll();
		OnRender();

		return true;
	}
	catch (...)
	{
		// if there's an exception, safely crash the game
		return false;
	}
}

void GameplayManager::OnUpdate()
{	
	UpdatePlayer();
	UpdateGrass();
	UpdateEnemies();

	Graphics::MoveCameraTo(player->body.getRect());
}

void GameplayManager::UpdatePlayer()
{
	bool playerIsMoving = false;

	int playerSpeedModifier = 1;

	// check for sprint
	if (sprintCooldown > 0)
	{
		// sprint for 120 frames
		if (sprintCooldown >= SPRINT_COOLDOWN - SPRINT_DURATION)
		{
			playerSpeedModifier = SPRINT_MODIFIER;
		}

		char timerText[5];
		_itoa_s(sprintCooldown / 6, timerText, 10);
		sprintTimer->setText(timerText);
		sprintTimer->visable = true;

		sprintCooldown--;
		sprintIcon->play("onCooldown");
	}
	else
	{
		sprintIcon->play("canUse");
		sprintTimer->visable = false;

		if (EventHandler::events[SPACE_KEY].held || EventHandler::controller->IsRThumbPressed())
		{
			sprintCooldown = SPRINT_COOLDOWN;
		}
	}

	// check for saws
	if (sawCooldown > 0)
	{
		if (sawCooldown >= SAW_COOLDOWN - SAW_DURATION)
		{
			for (int i = 0; i < NUM_SAWS; i++)
			{
				saws[i]->visable = true;
				saws[i]->transform.rot += 15;

				if (i == 0) { saws[i]->transform.x += SAW_SPEED; }
				else if (i == 1) { saws[i]->transform.x -= SAW_SPEED; }
				else if (i == 2) { saws[i]->transform.y += SAW_SPEED; }
				else if (i == 3) { saws[i]->transform.y -= SAW_SPEED; }

				KillHitEnemies(&saws[i]->body);
			}
		}
		else
		{
			for (int i = 0; i < NUM_SAWS; i++)
			{
				saws[i]->visable = false;
			}
		}

		char timerText[5];
		_itoa_s(sawCooldown / 6, timerText, 10);
		sawTimer->setText(timerText);
		sawTimer->visable = true;

		sawCooldown--;
		sawIcon->play("onCooldown");
	}
	else
	{
		sawIcon->play("canUse");
		sawTimer->visable = false;

		if (EventHandler::events[X_KEY].held || EventHandler::controller->IsAPressed())
		{
			sawCooldown = SAW_COOLDOWN;
			
			for (int i = 0; i < NUM_SAWS; i++)
			{
				saws[i]->transform.x = player->body.getRect().x + player->body.getRect().w / 2 - saws[i]->transform.w / 2;
				saws[i]->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - saws[i]->transform.h / 2;
			}
		}
	}

	// check for sword
	if (swordCooldown > 0)
	{
		if (swordCooldown >= SWORD_COOLDOWN - SWORD_DURATION)
		{
			sword->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - sword->transform.h / 2;

			if (sword->flip)
			{
				sword->transform.x = player->body.getRect().x - sword->transform.w;
			}
			else
			{
				sword->transform.x = player->body.getRect().x + player->body.getRect().w;
			}

			KillHitEnemies(&sword->body);
		}
		else
		{
			sword->visable = false;
		}

		char timerText[5];
		_itoa_s(swordCooldown / 6, timerText, 10);
		swordTimer->setText(timerText);
		swordTimer->visable = true;

		swordCooldown--;
		swordIcon->play("onCooldown");
	}
	else
	{
		swordIcon->play("canUse");
		swordTimer->visable = false;

		if (EventHandler::events[Z_KEY].held || EventHandler::controller->IsXPressed())
		{
			swordCooldown = SWORD_COOLDOWN;
			sword->visable = true;

			sword->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - sword->transform.h / 2;

			if (player->flip)
			{
				sword->transform.x = player->body.getRect().x - sword->transform.w;
				sword->flip = true;
			}
			else
			{
				sword->transform.x = player->body.getRect().x + player->body.getRect().w;
				sword->flip = false;
			}

			sword->play("swing", true);
		}
	}

	// check for axe
	if (axeCooldown > 0)
	{
		if (axeCooldown >= AXE_COOLDOWN - AXE_DURATION)
		{
			axe->transform.y += INIT_AXE_SPEED - floor((axeCooldown - AXE_COOLDOWN) * AXE_SPEED_CHANGE);
			axe->transform.rot += 7;
			KillHitEnemies(&axe->body);
		}
		else
		{
			axe->visable = false;
		}

		char timerText[5];
		_itoa_s(axeCooldown / 6, timerText, 10);
		axeTimer->setText(timerText);
		axeTimer->visable = true;

		axeCooldown--;
		axeIcon->play("onCooldown");
	}
	else
	{
		axe->visable = false;
		axeIcon->play("canUse");
		axeTimer->visable = false;

		if (EventHandler::events[C_KEY].held || EventHandler::controller->GetRightTriggerValue() > 0.5)
		{
			axeCooldown = AXE_COOLDOWN;
			axe->visable = true;

			axe->transform.x = player->body.getRect().x + player->body.getRect().w / 2 - axe->transform.w / 2;
			axe->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - axe->transform.h / 2;
		}
	}

	// movement and animation
	if (EventHandler::events[UP_KEY].held || EventHandler::controller->GetStickLYValue() > 0.2 || EventHandler::controller->IsDPUpPressed())
	{
		playerIsMoving = true;
		player->transform.y -= PLAYER_MOVE_SPEED * playerSpeedModifier;
		player->play("knight_walk");
	}
	if (EventHandler::events[DOWN_KEY].held || EventHandler::controller->GetStickLYValue() < -0.2 || EventHandler::controller->IsDPDownPressed())
	{
		playerIsMoving = true;
		player->transform.y += PLAYER_MOVE_SPEED * playerSpeedModifier;
		player->play("knight_walk");
	}
	if (EventHandler::events[RIGHT_KEY].held || EventHandler::controller->GetStickLXValue() > 0.2 || EventHandler::controller->IsDPRightPressed())
	{
		playerIsMoving = true;
		player->transform.x += PLAYER_MOVE_SPEED * playerSpeedModifier;
		player->flip = false;
		player->play("knight_walk");
	}
	if (EventHandler::events[LEFT_KEY].held || EventHandler::controller->GetStickLXValue() < -0.2 || EventHandler::controller->IsDPLeftPressed())
	{
		playerIsMoving = true;
		player->transform.x -= PLAYER_MOVE_SPEED * playerSpeedModifier;
		player->flip = true;
		player->play("knight_walk");
	}
	if (!playerIsMoving)
	{
		player->play("knight_idle");
	}

	// check if touching an enemy, and damage self if so
	if (IsTouchEnemy(&player->body))
	{
		UpdateHealth(-1);

		// kill self if dead?
		if (health <= 0)
		{
			GameOver();
		}
	}
}

void GameplayManager::UpdateGrass()
{
	// move grass tiles to fill screen
	for (int i = 0; i < NUM_GRASS; i++)
	{
		if (grass[i]->transform.x > Graphics::WINDOW_WIDTH + Graphics::cameraX)
		{
			grass[i]->transform.x -= grass[i]->transform.w * NUM_GRASS_X;
		}
		else if (grass[i]->transform.x + grass[i]->transform.w < Graphics::cameraX)
		{
			grass[i]->transform.x += grass[i]->transform.w * NUM_GRASS_X;
		}

		if (grass[i]->transform.y > Graphics::WINDOW_HEIGHT + Graphics::cameraY)
		{
			grass[i]->transform.y -= grass[i]->transform.h * NUM_GRASS_Y;
		}
		else if (grass[i]->transform.y + grass[i]->transform.h < Graphics::cameraY)
		{
			grass[i]->transform.y += grass[i]->transform.h * NUM_GRASS_Y;
		}
	}
}

void GameplayManager::UpdateEnemies()
{
	int spawnThreshold = INIT_ENEMY_SPAWN_SPEED - floor(score / SCORE_SPEED_UP_THRESHOLD);
	if (spawnThreshold < MAX_ENEMY_SPAWN_SPEED) spawnThreshold = MAX_ENEMY_SPAWN_SPEED;

	// if there are no enemies, spawn one in
	if (enemies.empty())
	{
		CreateEnemy();
		spawnCooldown = spawnThreshold;
	}

	// check if an enemy can be spawned in
	if (spawnCooldown <= 0)
	{
		CreateEnemy();
		spawnCooldown = spawnThreshold;
	}

	// move all enemies towards the player
	for (GameObject* enemy : enemies)
	{
		if (enemy->transform.x + enemy->transform.w / 2 > player->transform.x + player->transform.w / 2)
		{
			enemy->transform.x -= ENEMY_MOVE_SPEED;
			enemy->flip = true;
		}
		else if (enemy->transform.x + enemy->transform.w / 2 < player->transform.x + player->transform.w / 2)
		{
			enemy->transform.x += ENEMY_MOVE_SPEED;
			enemy->flip = false;
		}

		if (enemy->transform.y + enemy->transform.h / 2 > player->transform.y + player->transform.h / 2)
		{
			enemy->transform.y -= ENEMY_MOVE_SPEED;
		}
		else if (enemy->transform.y + enemy->transform.h / 2 < player->transform.y + player->transform.h / 2)
		{
			enemy->transform.y += ENEMY_MOVE_SPEED;
		}
	}

	spawnCooldown--;
}

void GameplayManager::KillHitEnemies(_Body* other)
{
	if (!enemies.empty())
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->body.checkCollision(*other))
			{
				objects.deleteObject(&enemies[i]);
				UpdateScore(SCORE_PER_KILL);
			}
		}
	}

	CleanNullEnemies();
}

void GameplayManager::CleanNullEnemies()
{
	queue<int> nullEnemies;

	if (!enemies.empty())
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i] == nullptr)
			{
				nullEnemies.push(i);
			}
		}
	}

	int numCleaned = 0;

	while (!nullEnemies.empty())
	{
		enemies.erase(enemies.begin() + (nullEnemies.front() - numCleaned));
		nullEnemies.pop();
		numCleaned++;
	}
}

bool GameplayManager::IsTouchEnemy(_Body* other)
{
	if (!enemies.empty())
	{
		for (GameObject* enemy : enemies)
		{
			if (enemy->body.checkCollision(*other))
			{
				return true;
			}
		}
	}
	
	return false;
}

void GameplayManager::CreateEnemy()
{
	GameObject* newEnemy;

	int spawnThreshold = INIT_ENEMY_SPAWN_SPEED - floor(score / SCORE_SPEED_UP_THRESHOLD);

	// get enemy type
	int type = floor(score / SCORE_ENEMY_TYPE_SWITCH_THRESHOLD);

	// flying eye
	if (type == 0)
	{
		newEnemy = objects.createSprite(0, 0, 0, "flyEye");
		newEnemy->play("flying");
		newEnemy->body.setOffset(20, 15);
		newEnemy->body.setSize(20, 20);
	}
	
	// goblin
	else if (type == 1)
	{
		newEnemy = objects.createSprite(0, 0, 0, "goblin");
		newEnemy->play("goblin_walk");
		newEnemy->body.setOffset(15, 17);
		newEnemy->body.setSize(20, 33);
	}

	// shroom
	else if (type == 2)
	{
		newEnemy = objects.createSprite(0, 0, 0, "shroom");
		newEnemy->play("shroom_walk");
		newEnemy->body.setOffset(12, 15);
		newEnemy->body.setSize(26, 35);
	}

	// skeleton
	else
	{
		newEnemy = objects.createSprite(0, 0, 0, "skeleton");
		newEnemy->play("skeleton_walk");
		newEnemy->body.setOffset(10, 0);
		newEnemy->body.setSize(30, 50);
	}

	// get random position
	int side = rand() % 4;

	// top of screen
	if (side == 0)
	{
		int pos = rand() % Graphics::WINDOW_WIDTH;
		newEnemy->transform.y = Graphics::cameraY - newEnemy->transform.h;
		newEnemy->transform.x = Graphics::cameraX + pos;
	}

	// right of screen
	else if (side == 2)
	{
		int pos = rand() % Graphics::WINDOW_HEIGHT;
		newEnemy->transform.x = Graphics::cameraX + Graphics::WINDOW_WIDTH;
		newEnemy->transform.y = Graphics::cameraY + pos;
	}

	// bottom of screen
	else if (side == 3)
	{
		int pos = rand() % Graphics::WINDOW_WIDTH;
		newEnemy->transform.y = Graphics::cameraY + Graphics::WINDOW_HEIGHT;
		newEnemy->transform.x = Graphics::cameraX + pos;
	}

	// left of screen
	else
	{
		int pos = rand() % Graphics::WINDOW_HEIGHT;
		newEnemy->transform.x = Graphics::cameraX - newEnemy->transform.w;
		newEnemy->transform.y = Graphics::cameraY + pos;
	}

	enemies.push_back(newEnemy);
}

void GameplayManager::UpdateHealth(int change)
{
	health += change;

	char num[15];
	_itoa_s(health, num, 10);

	string text = "HP: ";
	text.append(num);

	healthText->setText(text.c_str());
}

void GameplayManager::UpdateScore(int change)
{
	score += change;

	char num[15];
	_itoa_s(score, num, 10);

	string text = "SCORE: ";
	text.append(num);

	scoreText->setText(text.c_str());
}

void GameplayManager::OnRender()
{
	
}

void GameplayManager::Shutdown()
{
	leaderboard.Save();
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
