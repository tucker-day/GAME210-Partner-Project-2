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
	// sdl colours cant compare so... pain
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

void Text::render()
{
	Graphics::RenderGameObject(texture, NULL, &transform, 0, SDL_FLIP_NONE, followCamera);
}

void Text::updateText()
{
	_Texture newTexture = Graphics::CreateText(text, colour);

	texture = newTexture.texture;
	transform.h = fontSize;
	transform.w = fontSize * (newTexture.width / newTexture.height);
}
