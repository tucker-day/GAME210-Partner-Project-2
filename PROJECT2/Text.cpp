#include "Text.h"

#include "Graphics.h"

Text::Text(const char* newText, int x, int y, int fSize, int r, int g, int b)
	: transform(x, y, 0, 0, 0), text(newText), fontSize(fSize)
{
	colour = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
	updateText();
}

void Text::setColour(int r, int g, int b)
{
	if (r != colour.r || g != colour.g || b != colour.b)
	{
		colour = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
		updateText();
	}
}

void Text::setText(const char* newText)
{
	if (text != newText)
	{
		text = newText;
		updateText();
	}
}

void Text::setFontSize(int size)
{
	transform.w = size * (transform.w / transform.h);
	transform.h = size;

	fontSize = size;
}

void Text::setOrigin(float xy)
{
	originX = xy;
	originY = xy;
}

void Text::setOrigin(float x, float y)
{
	originX = x;
	originY = y;
}

void Text::render()
{
	if (visable)
	{
		// adjust for different origin
		_Transform temp = transform;

		temp.x -= temp.w * originX;
		temp.y -= temp.h * originY;

		Graphics::RenderGameObject(texture, NULL, &temp, 0, SDL_FLIP_NONE, followCamera);
	}
}

void Text::updateText()
{
	_Texture newTexture = Graphics::CreateText(text, colour);

	texture = newTexture.texture;
	transform.h = fontSize;
	transform.w = fontSize * (newTexture.width / newTexture.height);
}
