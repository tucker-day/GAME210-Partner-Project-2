#pragma once

#include "ObjData.h"
#include "GraphicsData.h"

class Text
{
public:
	Text(const char* newText, int x, int y, int fSize, int r = 0, int b = 0, int g = 0);
	~Text();

	void setColour(int r = 0, int g = 0, int b = 0);
	void setText(const char* text);
	void setFontSize(int size);
	void setOrigin(float x);
	void setOrigin(float x, float y);
	void setRotPoint(float x, float y) { rotPoint = { (int)round(transform.w * x), (int)round(transform.h * y) }; }

	void render();

	_Transform transform;
	bool followCamera = false;
	bool visable = true;

private:
	void updateText();

	SDL_Texture* texture;
	SDL_Color colour;
	SDL_Point rotPoint = { 0, 0 };
	float originX = 0, originY = 0;
	int fontSize;
	const char* text;
};