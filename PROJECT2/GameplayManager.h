#pragma once

#include "ObjectFactory.h"
#include "LoadManager.h"
#include "Leaderboard.h"

const int NUM_GRASS_X = 9;
const int NUM_GRASS_Y = 6;
const int NUM_GRASS = NUM_GRASS_X * NUM_GRASS_Y;

const short PLAYER_MOVE_SPEED = 2;

const short SPRINT_COOLDOWN = 60 * 5;
const short SPRINT_DURATION = 150;
const short SPRINT_MODIFIER = 2;

const short SAW_COOLDOWN = 60 * 5;
const short SAW_DURATION = 120;
const short SAW_SPEED = 8;
const short NUM_SAWS = 4;

const short SWORD_COOLDOWN = 60 * 0.75;
const short SWORD_DURATION = 18;

const short AXE_COOLDOWN = 60 * 2;
const short AXE_DURATION = 120;
const short INIT_AXE_SPEED = -9;
const float AXE_SPEED_CHANGE = 0.25;

const short SCORE_PER_KILL = 100;

const short INIT_ENEMY_SPAWN_SPEED = 16;
const short SCORE_SPEED_UP_THRESHOLD = 5000;
const short SCORE_ENEMY_TYPE_SWITCH_THRESHOLD = 20000;
const short MAX_ENEMY_SPAWN_SPEED = 2;
const short ENEMY_MOVE_SPEED = 1;

class GameplayManager
{
public:
	GameplayManager() : leaderboard("leaderboard.save") { Preload(); Init(); };
	~GameplayManager() {};

	void Update();
	void Render();
	void Shutdown();

	void updateNextTime();
	Uint32 frameTimeLeft();

private: 
	const int FRAME_RATE = 60;
	Uint32 nextTime;
	bool restartScene = false;

	void OnUpdate();
	void UpdatePlayer();
	void UpdateGrass();
	void UpdateEnemies();

	void KillHitEnemies(_Body* other);
	void CleanNullEnemies();
	bool IsTouchEnemy(_Body* other);
	void CreateEnemy();

	void UpdateHealth(int change);
	void UpdateScore(int change);

	void OnRender();

	void Preload();
	void Init();
	void Restart();
	void SystemControls();

	void GameOver();

	Leaderboard leaderboard;

	int health;
	int score;

	Text* healthText;
	Text* scoreText;

	GameObject* grass[NUM_GRASS];

	GameObject* player;

	GameObject* saws[NUM_SAWS];
	GameObject* sword;
	GameObject* axe;

	GameObject* sprintIcon;
	GameObject* sawIcon;
	GameObject* swordIcon;
	GameObject* axeIcon;

	Text* sprintTimer;
	Text* sawTimer;
	Text* swordTimer;
	Text* axeTimer;

	vector<GameObject*> enemies;

	int sprintCooldown;
	int sawCooldown;
	int swordCooldown;
	int axeCooldown;

	int spawnCooldown;

	bool gameOver;

	ObjectFactory objects;
};