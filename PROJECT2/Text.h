#pragma once

#include "ObjData.h"
#include "GraphicsData.h"

class Text
{
public:
	Text(const char* newText, int x, int y, int fSize, int r = 0, int b = 0, int g = 0);
	~Text() {};

	void setColour(int r = 0, int g = 0, int b = 0);
	void setText(const char* text);
	void setFontSize(int size);

	void render();

	_Transform transform;
	bool followCamera = false;
	bool visable = true;
	bool centered = false;

private:
	void updateText();

	SDL_Texture* texture;
	SDL_Color colour;
	int fontSize;
	const char* text;
};