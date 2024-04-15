#pragma once

#include "ObjectFactory.h"
#include "LoadManager.h"

class GameplayManager
{
public:
	GameplayManager() { Init(); };
	~GameplayManager() {};

	void Update();
	void Render();

	void updateNextTime();
	Uint32 frameTimeLeft();

private: 
	const int FRAME_RATE = 60;
	Uint32 nextTime;

	void Init();

	GameObject* player;
	GameObject* test;
	GameObject* uiTest;

	Text* textTest;
	Text* uiText;

	ObjectFactory objects;
};