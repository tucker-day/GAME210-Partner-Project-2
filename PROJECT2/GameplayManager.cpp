#include "GameplayManager.h"

#include "EventHandler.h"

#include <queue>

// load all sprite assets here
void GameplayManager::Preload()
{
	// knight loading and animation creation
	LoadManager::loadSprite("knight", "knightSheet.bmp", 40, 40);
	LoadManager::createAnimation("knight_walk", 0, 9, 4);
	LoadManager::createAnimation("knight_idle", 10, 19, 4);

	// loading grass sprite
	LoadManager::loadSprite("grass", "grass.bmp");

	// loading sprites for player abilities
	LoadManager::loadSprite("saw", "saw.bmp");
	LoadManager::loadSprite("axe", "axe.bmp");

	// sword loading and animation creation
	LoadManager::loadSprite("sword", "sword.bmp", 192, 64);
	LoadManager::createAnimation("swing", 0, 5, 2, 0);

	// loading ability icons for game ui
	LoadManager::loadSprite("sprint", "sprint.bmp", 64);
	LoadManager::loadSprite("sawIcon", "sawIcon.bmp", 64);
	LoadManager::loadSprite("swordIcon", "swordIcon.bmp", 64);
	LoadManager::loadSprite("axeIcon", "axeIcon.bmp", 64);

	// animations for ability icons
	LoadManager::createAnimation("onCooldown", 0, 0);
	LoadManager::createAnimation("canUse", 1, 1);

	// loading flying eye enemy and creating animations
	LoadManager::loadSprite("flyEye", "flyingEye.bmp", 60, 50);
	LoadManager::createAnimation("flying", 0, 7, 5);

	// loading goblin enemy and create animation
	LoadManager::loadSprite("goblin", "goblin.bmp", 50, 50);
	LoadManager::createAnimation("goblin_walk", 0, 7, 5);

	// loading shroom enemy and create animation
	LoadManager::loadSprite("shroom", "shroom.bmp", 50, 50);
	LoadManager::createAnimation("shroom_walk", 0, 7, 5);

	// loading skeleton enemy and create animation
	LoadManager::loadSprite("skeleton", "skeleton.bmp", 50, 50);
	LoadManager::createAnimation("skeleton_walk", 0, 3, 5);
}

void GameplayManager::Init()
{
	// creating the grass objects
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

	// creating icon for sprint ability
	sprintIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "sprint", 1);
	sprintIcon->followCamera = true;

	// creating control instructions for sprint ability
	Text* uiText = objects.createText("Space / L3", sprintIcon->transform.x + sprintIcon->transform.w / 2, sprintIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	// creating the timer for sprint ability
	sprintTimer = objects.createText("0", sprintIcon->transform.x + sprintIcon->transform.w / 2, sprintIcon->transform.y + sprintIcon->transform.h / 2, 30, 255, 255, 255, false);
	sprintTimer->setOrigin(0.5);
	sprintTimer->followCamera = true;

	// set sprint ability cooldown to 0
	sprintCooldown = 0;

	// creating the icon for the axe ability
	axeIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94 * 2, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "axeIcon", 1);
	axeIcon->followCamera = true;

	// creating control instructions for axe ability
	uiText = objects.createText("C Key / RT", axeIcon->transform.x + axeIcon->transform.w / 2, axeIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	// creating the timer text for axe ability
	axeTimer = objects.createText("0", axeIcon->transform.x + axeIcon->transform.w / 2, axeIcon->transform.y + axeIcon->transform.h / 2, 30, 255, 255, 255, false);
	axeTimer->setOrigin(0.5);
	axeTimer->followCamera = true;

	// set the ability cooldown
	axeCooldown = 0;

	// create the axe sprite
	axe = objects.createSprite(0, 0, 0, "axe", 0, false);

	// create the icon for the saw ability
	sawIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94 * 3, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "sawIcon", 1);
	sawIcon->followCamera = true;

	// create the controls insstructions for the saw ability
	uiText = objects.createText("X Key / A Button", sawIcon->transform.x + sawIcon->transform.w / 2, sawIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	// create the timer text for the saw ability
	sawTimer = objects.createText("0", sawIcon->transform.x + sawIcon->transform.w / 2, sawIcon->transform.y + sawIcon->transform.h / 2, 30, 255, 255, 255, false);
	sawTimer->setOrigin(0.5);
	sawTimer->followCamera = true;

	// set the saw ability cooldown to 0
	sawCooldown = 0;

	// create all the saw objects
	for (int i = 0; i < NUM_SAWS; i++)
	{
		saws[i] = objects.createSprite(0, 0, 0, "saw", 0, false);
	}

	// create the icon for the sword ability
	swordIcon = objects.createSprite(Graphics::WINDOW_WIDTH - 94 * 4, Graphics::WINDOW_HEIGHT - 64 - 20, 0, "swordIcon", 1);
	swordIcon->followCamera = true;

	// create the controls instructions for the sword ability
	uiText = objects.createText("Z Key / X Button", swordIcon->transform.x + swordIcon->transform.w / 2, swordIcon->transform.y - 5, 10, 255, 255, 255);
	uiText->followCamera = true;
	uiText->setOrigin(0.5, 1);

	// create the timer text for the sword ability
	swordTimer = objects.createText("0", swordIcon->transform.x + swordIcon->transform.w / 2, swordIcon->transform.y + swordIcon->transform.h / 2, 30, 255, 255, 255, false);
	swordTimer->setOrigin(0.5);
	swordTimer->followCamera = true;

	// set the sword cooldown to 0
	swordCooldown = 0;

	// create the sword object
	sword = objects.createSprite(0, 0, 0, "sword", 0, false);

	// creating assorted controls instructions
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

	// creating the health and score text
	health = 100;
	healthText = objects.createText("HP: 100", Graphics::WINDOW_WIDTH / 2, Graphics::WINDOW_HEIGHT - 60, 25, 255, 255, 255);
	healthText->followCamera = true;
	healthText->setOrigin(0.5, 1);

	score = 0;
	scoreText = objects.createText("SCORE: 0", Graphics::WINDOW_WIDTH / 2, Graphics::WINDOW_HEIGHT - 30, 25, 255, 255, 255);
	scoreText->followCamera = true;
	scoreText->setOrigin(0.5, 1);

	// set up enemy spawn cooldown
	spawnCooldown = INIT_ENEMY_SPAWN_SPEED;
}

void GameplayManager::Restart()
{
	// delete all the objects in the game world
	objects.deleteAllObjects();
	objects.deleteAllText();

	// clear the enemy vector
	enemies.clear();

	// re-init the game
	Init();

	// prevent the game from restarting again until asked
	restartScene = false;

	// make sure the player is alive
	gameOver = false;
}

void GameplayManager::SystemControls()
{
	// full screen toggle controls
	if (EventHandler::events[F11_KEY].pressed) {
		Graphics::ToggleFullscreen();
	}

	// game restart controls
	if (EventHandler::events[R_KEY].pressed) {
		restartScene = true;
	}
}

void GameplayManager::GameOver()
{
	// kill the player
	gameOver = true;

	// add the player's score to the leaderboard
	leaderboard.AddEntry(score);

	// create the game over text on the right of the screen
	Text* temp = objects.createText("GAME OVER", 50, Graphics::WINDOW_HEIGHT / 2, 50, 255, 255, 255);
	temp->setOrigin(0, 1);
	temp->followCamera = true;

	// get the player's final score as a string
	char num[15];
	_itoa_s(score, num, 10);

	// display the player's final score under the game over text
	string text = "Final Score: ";
	text.append(num);
	
	temp = objects.createText(text.c_str(), 50, Graphics::WINDOW_HEIGHT / 2 - 1, 25, 255, 255, 255);
	temp->followCamera = true;

	// create the leaderboard on the left side of the screen
	temp = objects.createText("LEADERBOARD", Graphics::WINDOW_WIDTH - 50, Graphics::WINDOW_HEIGHT / 2 - 200, 25, 255, 255, 255);
	temp->setOrigin(1, 0);
	temp->followCamera = true;

	// display all of the leaderboard entries under the leaderboard header
	for (int i = 0; i < MAX_ENTRIES; i++)
	{
		// get the score as a string
		_itoa_s(leaderboard.GetEntry(i), num, 10);

		// make the text element
		temp = objects.createText(num, Graphics::WINDOW_WIDTH - 50, Graphics::WINDOW_HEIGHT / 2 - 200 + 30 * (i + 1), 25, 255, 255, 255);
		temp->setOrigin(1, 0);
		temp->followCamera = true;

		// if the score is the same ass the player's, highlight it red
		if (leaderboard.GetEntry(i) == score)
		{
			temp->setColour(255, 0, 0);
		}
	}

	// save the leaderboard as a file
	leaderboard.Save();
}

void GameplayManager::Update()
{
	SystemControls();
	
	if (restartScene) { Restart(); }

	if (!gameOver)
	{
		OnUpdate();
		objects.updateAll();
	}
}

void GameplayManager::Render()
{
	objects.renderAll();
	OnRender();
}

void GameplayManager::OnUpdate()
{	
	UpdatePlayer();
	UpdateGrass();
	UpdateEnemies();

	// move the camera to the player's body
	Graphics::MoveCameraTo(player->body.getRect());
}

void GameplayManager::UpdatePlayer()
{
	bool playerIsMoving = false;
	int playerSpeedModifier = 1;

	// check if sprint is on cooldown
	if (sprintCooldown > 0)
	{
		// sprint for the duration after ability usage
		if (sprintCooldown >= SPRINT_COOLDOWN - SPRINT_DURATION)
		{
			playerSpeedModifier = SPRINT_MODIFIER;
		}

		// update timer
		char timerText[5];
		_itoa_s(sprintCooldown / 6, timerText, 10);
		sprintTimer->setText(timerText);
		sprintTimer->visable = true;

		// reduce the cooldown
		sprintCooldown--;

		// make the icon be on cooldown
		sprintIcon->play("onCooldown");
	}
	else
	{
		// make the icon on use
		sprintIcon->play("canUse");

		// make the timer invisable
		sprintTimer->visable = false;

		// check if the player activated the ability
		if (EventHandler::events[SPACE_KEY].held || EventHandler::controller->IsLThumbPressed())
		{
			sprintCooldown = SPRINT_COOLDOWN;
		}
	}

	// check for saws on cooldown
	if (sawCooldown > 0)
	{
		// move the sawblades for the duration after ability use
		if (sawCooldown >= SAW_COOLDOWN - SAW_DURATION)
		{
			// go through all the saws
			for (int i = 0; i < NUM_SAWS; i++)
			{
				// make sure the saws are visable and rotate them
				saws[i]->visable = true;
				saws[i]->transform.rot += 15;

				// move the saws based on it's index in the array
				if (i == 0) { saws[i]->transform.x += SAW_SPEED; }
				else if (i == 1) { saws[i]->transform.x -= SAW_SPEED; }
				else if (i == 2) { saws[i]->transform.y += SAW_SPEED; }
				else if (i == 3) { saws[i]->transform.y -= SAW_SPEED; }

				// kill any enemies hit by the saw
				KillHitEnemies(&saws[i]->body);
			}
		}
		else
		{
			// if after duration, make sure the saws are invisable
			for (int i = 0; i < NUM_SAWS; i++)
			{
				saws[i]->visable = false;
			}
		}

		// update the timer text
		char timerText[5];
		_itoa_s(sawCooldown / 6, timerText, 10);
		sawTimer->setText(timerText);
		sawTimer->visable = true;

		// reduce the cooldown
		sawCooldown--;

		// make the icon on cooldown
		sawIcon->play("onCooldown");
	}
	else
	{
		// make the icon on use
		sawIcon->play("canUse");

		// make sure the timer is invisable
		sawTimer->visable = false;

		// check if the player used the ability
		if (EventHandler::events[X_KEY].held || EventHandler::controller->IsAPressed())
		{
			// put the ability on cooldown
			sawCooldown = SAW_COOLDOWN;
			
			// move all the saws to the player's position
			for (int i = 0; i < NUM_SAWS; i++)
			{
				saws[i]->transform.x = player->body.getRect().x + player->body.getRect().w / 2 - saws[i]->transform.w / 2;
				saws[i]->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - saws[i]->transform.h / 2;
			}
		}
	}

	// check for sword on cooldown
	if (swordCooldown > 0)
	{
		// update the sword for the duration
		if (swordCooldown >= SWORD_COOLDOWN - SWORD_DURATION)
		{
			// move the sword to the player
			sword->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - sword->transform.h / 2;

			// have the sword point out from the player in the correct direction based on its flip
			sword->transform.x = player->body.getRect().x + ((sword->flip) ? -sword->transform.w : player->body.getRect().w);

			// kill any enemies hit by the sword
			KillHitEnemies(&sword->body);
		}
		else
		{
			// make the sword invisable outside of duration
			sword->visable = false;
		}

		// update the timer
		char timerText[5];
		_itoa_s(swordCooldown / 6, timerText, 10);
		swordTimer->setText(timerText);
		swordTimer->visable = true;

		// reduce the cooldown
		swordCooldown--;

		// make the icon on cooldown
		swordIcon->play("onCooldown");
	}
	else
	{
		// make the icon off cooldown
		swordIcon->play("canUse");

		// make sure the timer isn't visable
		swordTimer->visable = false;

		// check if the player used the ability
		if (EventHandler::events[Z_KEY].held || EventHandler::controller->IsXPressed())
		{
			// set the cooldown
			swordCooldown = SWORD_COOLDOWN;

			// make the sword visable
			sword->visable = true;

			// move the sword to the player
			sword->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - sword->transform.h / 2;

			// have the sword point out in the correct direction and face in the
			// correct direction based on player flip
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

			// make the sword player the swing animation
			sword->play("swing", true);
		}
	}

	// check for axe on cooldown
	if (axeCooldown > 0)
	{
		// update the axe for the duration
		if (axeCooldown >= AXE_COOLDOWN - AXE_DURATION)
		{
			// move the axe down at a faster rate over the duration and rotate
			axe->transform.y += INIT_AXE_SPEED - floor((axeCooldown - AXE_COOLDOWN) * AXE_SPEED_CHANGE);
			axe->transform.rot += 7;

			// kill all enemies hit
			KillHitEnemies(&axe->body);
		}
		else
		{
			// off duration, make the axe invisable
			axe->visable = false;
		}

		// update the timer text
		char timerText[5];
		_itoa_s(axeCooldown / 6, timerText, 10);
		axeTimer->setText(timerText);
		axeTimer->visable = true;

		// reduce ability cooldown
		axeCooldown--;

		// make the icon on cooldown
		axeIcon->play("onCooldown");
	}
	else
	{
		// make ssure the axe is invisable
		axe->visable = false;

		// make the icon off cooldown
		axeIcon->play("canUse");

		// make sure the timer is invisable
		axeTimer->visable = false;

		// check if the player used the ability
		if (EventHandler::events[C_KEY].held || EventHandler::controller->GetRightTriggerValue() > 0.5)
		{
			// set the cooldown
			axeCooldown = AXE_COOLDOWN;

			// make the axe visable
			axe->visable = true;

			// move the axe to the center of the player
			axe->transform.x = player->body.getRect().x + player->body.getRect().w / 2 - axe->transform.w / 2;
			axe->transform.y = player->body.getRect().y + player->body.getRect().h / 2 - axe->transform.h / 2;
		}
	}

	// player movement and animation
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

		// kill self if dead
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
		// horizontal adjustments
		if (grass[i]->transform.x > Graphics::WINDOW_WIDTH + Graphics::cameraX)
		{
			grass[i]->transform.x -= grass[i]->transform.w * NUM_GRASS_X;
		}
		else if (grass[i]->transform.x + grass[i]->transform.w < Graphics::cameraX)
		{
			grass[i]->transform.x += grass[i]->transform.w * NUM_GRASS_X;
		}

		// vertical adjustments
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
	// calculate the spawn threshold
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
		// horizontal movement
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

		// vertical movement
		if (enemy->transform.y + enemy->transform.h / 2 > player->transform.y + player->transform.h / 2)
		{
			enemy->transform.y -= ENEMY_MOVE_SPEED;
		}
		else if (enemy->transform.y + enemy->transform.h / 2 < player->transform.y + player->transform.h / 2)
		{
			enemy->transform.y += ENEMY_MOVE_SPEED;
		}
	}

	// reduce spawn cooldown
	spawnCooldown--;
}

void GameplayManager::KillHitEnemies(_Body* other)
{
	if (!enemies.empty())
	{
		// go through all enemies and see if they hit the other body
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->body.checkCollision(*other))
			{
				// if hit, delete the enemy and update score
				objects.deleteObject(&enemies[i]);
				UpdateScore(SCORE_PER_KILL);
			}
		}
	}

	// clean the null enemies out of the enemies vector
	CleanNullEnemies();
}

void GameplayManager::CleanNullEnemies()
{
	queue<int> nullEnemies;

	// go through the enemies vector and collect the id's of null enemies
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

	// erase all null enemies from the vector
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
	// go through all enemies and return if it collides with the other body
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

	// get enemy type for creation
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

	// set the enemy position to a random place on randomized side.
	// get random size to place the enemy on
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

	// put the new created enemy into the vector
	enemies.push_back(newEnemy);
}

void GameplayManager::UpdateHealth(int change)
{
	// change the player's health
	health += change;

	// update the health display text
	char num[15];
	_itoa_s(health, num, 10);

	string text = "HP: ";
	text.append(num);

	healthText->setText(text.c_str());
}

void GameplayManager::UpdateScore(int change)
{
	// change the score
	score += change;

	// update the score display text
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
	// save the leaderboard on shutdown
	leaderboard.Save();

	// delete all the objects in the game world
	objects.deleteAllObjects();
	objects.deleteAllText();

	// clear the enemy vector
	enemies.clear();
}

void GameplayManager::updateNextTime()
{
	// CODE IS BASED OFF YASH'S SDL TEMPLATE
	
	// sets when the next frame should be played based on framerate
	nextTime = SDL_GetTicks() + 1000 / FRAME_RATE;
}

Uint32 GameplayManager::frameTimeLeft()
{
	// CODE IS BASED OFF YASH'S SDL TEMPLATE

	// get the current time
	Uint32 now = SDL_GetTicks();

	// return how much time is left for the frame
	if (nextTime <= now)
		return 0;
	else
		return nextTime - now;
}
