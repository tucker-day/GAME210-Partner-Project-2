#pragma once

#include "LoadManager.h"
#include "ObjectFactory.h"

// container for the load manager and objent factory
class ObjectManager 
{
public:
	ObjectManager();
	~ObjectManager() {};

	LoadManager load;
	ObjectFactory add;

private:
	// create the objects
	vector<GameObject>* Objects;
	vector<_Sprite>* Sprites;
	vector<_Anim>* Anims;
};