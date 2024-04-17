#pragma once

#include "ObjectFactory.h"
#include "LoadManager.h"

class GameplayManager
{
public:
	GameplayManager() { Preload(); Init(); };
	~GameplayManager() {};

	void Update();
	void Render();

	void updateNextTime();
	Uint32 frameTimeLeft();

private: 
	const int FRAME_RATE = 60;
	Uint32 nextTime;
	bool restartScene = false;

	void Preload();
	void Init();
	void Restart();

	GameObject* player;
	GameObject* test;
	GameObject* uiTest;

	Text* textTest;
	Text* uiText;

	ObjectFactory objects;
};