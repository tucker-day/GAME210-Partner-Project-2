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

private: 
	void Init();

	GameObject* player;
	GameObject* test;

	ObjectFactory objects;
};