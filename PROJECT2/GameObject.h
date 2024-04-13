#pragma once

#include "SDL.h"

#include "ObjData.h"
#include "Body.h"
#include "GraphicsData.h"
#include "Animator.h"

class GameObject
{
public:
	GameObject(_Sprite* s, _Body b, _Transform t, int f, bool v);
	~GameObject() {};

	_Body body;
	_Transform transform;

	void play(const char* key);

	virtual void render();
	virtual void update();

private:
	_Sprite* sprite;
	_Animator animator;
	bool visable;
};