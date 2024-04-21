#include "ObjectFactory.h"

#include <vector>

ObjectFactory::ObjectFactory()
{
	// create the game objects vector
	Objects = new vector<GameObject*>();
	TextElements = new vector<Text*>();
}

ObjectFactory::~ObjectFactory()
{
	deleteAllObjects();

	delete Objects;
}

void ObjectFactory::updateAll()
{
	// updates all objects in the factory
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
	// render all objects in the factory
	if (!Objects->empty())
	{
		// all sprite game objects
		for (GameObject* object : *Objects)
		{
			if (object != nullptr)
			{
				object->render();
			}
		}

		// render all the text elements
		if (!TextElements->empty())
		{
			for (Text* object : *TextElements)
			{
				if (object != nullptr)
				{
					object->render();
				}
			}
		}

		// if rendering bodies, render all the bodies
		if (Graphics::RENDER_BODIES)
		{
			for (GameObject* object : *Objects)
			{
				if (object != nullptr)
				{
					object->body.render(object->followCamera);
				}
			}
		}
	}
}

GameObject* ObjectFactory::createSprite(int x, int y, int rot, const char* key, short frame, bool visable)
{
	// get the sprite
	_Sprite* sprite = LoadManager::getSprite(key);

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

Text* ObjectFactory::createText(const char* text, int x, int y, int fontSize, int r, int g, int b, bool visable)
{
	Text* newText = new Text(text, x, y, fontSize, r, g, b);
	newText->visable = visable;

	TextElements->push_back(newText);

	return newText;
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

			// delete the object out of heap
			delete* object;

			// make the passed pointer a null pointer
			*object = nullptr;

			break;
		}
	}
}

void ObjectFactory::deleteAllObjects()
{
	// delete all the objects
	for (int i = 0; i < Objects->size(); i++)
	{
		delete Objects->at(i);
	}

	// clear all the pointers
	Objects->clear();
}

void ObjectFactory::deleteText(Text** element)
{
	// check if the object is inside of the objects vector and erase it if it is
	for (unsigned int i = 0; i < TextElements->size(); i++)
	{
		if (TextElements->at(i) == *element)
		{
			TextElements->erase(TextElements->begin() + i);
			break;
		}
	}

	// delete the object out of heap
	delete* element;

	// make the passed pointer a null pointer
	*element = nullptr;
}

void ObjectFactory::deleteAllText()
{
	// delete all the objects
	for (int i = 0; i < TextElements->size(); i++)
	{
		delete TextElements->at(i);
	}

	// clear all the pointers
	TextElements->clear();
}
