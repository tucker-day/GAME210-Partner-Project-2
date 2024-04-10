#include "ObjectFactory.h"

#include <vector>

ObjectFactory::ObjectFactory()
{
	// create the game objects vector
	Objects = new vector<GameObject*>();
}

ObjectFactory::~ObjectFactory()
{
	deleteAllObjects();

	delete Objects;
}

void ObjectFactory::updateAll()
{
	if (!Objects->empty())
	{
		for (GameObject* object : *Objects)
		{
			if (object != nullptr)
			{
				object->update();
			}
		}
	}
}

void ObjectFactory::renderAll()
{
	if (!Objects->empty())
	{
		for (GameObject* object : *Objects)
		{
			if (object != nullptr)
			{
				object->render();
			}
		}
	}
}

GameObject* ObjectFactory::createSprite(int x, int y, int rot, const char* key, short frame, bool visable)
{
	// get the sprite
	_Sprite* sprite = loadManager.getSprite(key);

	// create the body so its in the same position and size as the parent
	_Body body = _Body({ x, y, sprite->frameWidth, sprite->frameHeight });

	// create the transform
	_Transform transform = _Transform(body.getRect(), rot);

	// create the game object and add it to the objects vector
	GameObject* obj = new GameObject(sprite, body, transform, frame, visable);
	Objects->push_back(obj);

	// return the pointer to the new object
	return obj;
}

// WARNING: i have not tested this yet so im not sure if it'll break stuff. you have been warned!
void ObjectFactory::addExisting(GameObject* object)
{
	Objects->push_back(object);
}

void ObjectFactory::deleteObject(GameObject** object)
{
	// check if the object is inside of the objects vector and erase it if it is
	for (unsigned int i = 0; i < Objects->size(); i++)
	{
		if (Objects->at(i) == *object)
		{
			Objects->erase(Objects->begin() + i);
			break;
		}
	}

	// delete the object out of heap
	delete *object;

	// make the passed pointer a null pointer
	*object = nullptr;
}

void ObjectFactory::deleteAllObjects()
{
	// delete all the objects
	for (int i = 0; i < Objects->size(); i++)
	{
		delete Objects->at(i);
	}

	// clear all the pointers than shrink the vector
	Objects->clear();
	Objects->shrink_to_fit();
}
