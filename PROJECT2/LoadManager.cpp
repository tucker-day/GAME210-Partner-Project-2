#include "LoadManager.h"

vector<_Sprite*>* LoadManager::sprites;
vector<_Anim*>* LoadManager::animations;

void LoadManager::Init()
{
	// create the vectors
	sprites = new vector<_Sprite*>();
	animations = new vector<_Anim*>();

	// create a error texture
	loadSprite("error", "error.bmp");
}

void LoadManager::Shutdown()
{
	// delete all the sprites
	for (int i = 0; i < sprites->size(); i++) 
	{
		delete sprites->at(i);
	}

	// delete all the anims
	for (int i = 0; i < animations->size(); i++)
	{
		delete animations->at(i);
	}

	// clear the vectors, then delete them
	sprites->clear();
	delete sprites;

	animations->clear();
	delete animations;
}

void LoadManager::loadSprite(const char* key, const char* file, int spriteWidth, int spriteHeight)
{
	// check that an image with that key dosen't already exist
	if (!spriteKeyExists(key))
	{
		// create the texture
		_Texture texture = Graphics::CreateTexture(file);

		if (spriteWidth <= 0) 
		{
			spriteWidth = texture.width;
			spriteHeight = texture.height;
		}
		else if (spriteHeight <= 0) 
		{
			spriteHeight = spriteWidth;
		}

		// create a new sprite and add it to the vector
		_Sprite* temp = new _Sprite({ key, texture, spriteWidth, spriteHeight });
		sprites->push_back(temp);
	}
	else
	{
		// if an image with that key already exists, print an error
		printf("Sprite with key %s already exists", key);
	}
}

void LoadManager::createAnimation(const char* key, int startFrame, int endFrame, int frameDelay, int repeat)
{
	// check that an animation with that key does not already exist
	if (getAnim(key) == nullptr)
	{
		// create the animation and push
		_Anim* temp = new _Anim(key, startFrame, endFrame, frameDelay, repeat);
		animations->push_back(temp);
	}
	else
	{
		// if an anim with that key exists, print an error
		printf("Anim with key %s already exists", key);
	}
}

_Sprite* LoadManager::getSprite(const char* key)
{
	// loop through the sprites vector and return the sprite with the corosponding key
	if (sprites->size() != 0)
	{
		for (_Sprite* i : *sprites)
		{
			if (i->key == key)
			{
				return i;
			}
		}
	}

	// if there is no sprite with that key, return the error texture (kind of recursion i guess?)
	return getSprite("error");
}

bool LoadManager::spriteKeyExists(const char* key)
{
	// loop through the sprites vector and return true if key exists
	if (sprites->size() != 0)
	{
		for (_Sprite* i : *sprites)
		{
			if (i->key == key)
			{
				return true;
			}
		}
	}

	return false;
}

_Anim* LoadManager::getAnim(const char* key)
{
	// loop through the animation vector and return the sprite with the corosponding key
	if (animations->size() != 0)
	{
		for (_Anim* i : *animations)
		{
			if (i->key == key)
			{
				return i;
			}
		}
	}

	// if there is no animation with that key, return a null pointer
	return nullptr;
}
