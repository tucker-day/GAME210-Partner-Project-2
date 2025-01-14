#pragma once

#include <vector>
#include <stack>

#include "LoadManager.h"
#include "GameObject.h"
#include "Text.h"

using namespace std;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	// runs the update function of all game objects in the factory
	void updateAll();

	// runs the render function of all game objects in the factory
	void renderAll();

	// creates a game object with the given sprite and information, then returns a pointer. these objects
	// will be automatically rendered
	GameObject* createSprite(int x, int y, int rot, const char* key, short startFrame = 0, bool visable = true);

	Text* createText(const char* text, int x, int y, int fontSize, int r = 0, int g = 0, int b = 0, bool visable = true);

	// adds an already created object into the factory. this is useful to get objects created outside of
	// the factory into the factory's render loop
	void addExisting(GameObject* object);

	// deletes an object out of the vector
	void deleteObject(GameObject** object);

	// deletes every object in the vector
	void deleteAllObjects();

	// deletes a text element
	void deleteText(Text** element);

	// deletes every text element
	void deleteAllText();

private:
	// create a pointer to a vector of game object pointers
	vector<GameObject*>* Objects;

	// pointer to text elements
	vector<Text*>* TextElements;
};