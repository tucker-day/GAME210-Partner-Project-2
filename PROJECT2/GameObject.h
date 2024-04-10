#pragma once

#include "SDL.h"

#include "GraphicsData.h"
#include "ObjData.h"
#include "Body.h"

class GameObject
{
public:
	GameObject(_Sprite* s, _Body b, _Transform t, int f, bool v) :
		sprite(s), body(b), transform(t), frame(f), visable(v) {};
	~GameObject() {};

	_Body body;
	_Transform transform;

	void changeFrame() { frame++; }

	virtual void render();
	virtual void update();

private:
	_Sprite* sprite;
	unsigned int frame;
	bool visable;
};