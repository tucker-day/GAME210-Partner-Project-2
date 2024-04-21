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
	bool followCamera = false;
	bool visable;
	bool flip = false;

	void play(const char* key, bool overide = false);
	void setRotPoint(float x, float y) { rotPoint = { (int)round(transform.w * x), (int)round(transform.h * y) }; }

	virtual void render();
	virtual void update();

private:
	_Sprite* sprite;
	_Animator animator;
	SDL_Point rotPoint = { 0, 0 };
};