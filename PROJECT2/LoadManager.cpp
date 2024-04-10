#include "LoadManager.h"

LoadManager::LoadManager()
{
	// create the vector
	sprites = new vector<_Sprite*>();
}

LoadManager::~LoadManager()
{
	// delete all the sprites
	for (int i = 0; i < sprites->size(); i++) 
	{
		delete sprites->at(i);
	}

	// clear the vector, then delete that as well
	sprites->clear();
	delete sprites;
}

void LoadManager::loadSprite(const char* key, const char* file, int spriteWidth, int spriteHeight)
{
	// check that an image with that key dosen't already exist
	if (getSprite(key) == nullptr) 
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

	// if there is no sprite with that key, return a null pointer
	return nullptr;
}
