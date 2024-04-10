#pragma once

#include <vector>

#include "SDL.h"
#include <SDL_ttf.h>

#include "ObjData.h"
#include "GraphicsData.h"

using namespace std;

class Graphics
{
public:
	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;
	static const bool RENDER_BODIES = true;

	static SDL_Renderer* renderer;

	static bool Init();

	static void StartRender();
	static void EndRender();

	static void Shutdown() { TTF_CloseFont(font); };

	// creates a texture from a bmp file
	static _Texture CreateTexture(const char* file);

	static void RenderGameObject(SDL_Texture* texture, SDL_Rect* src, _Transform* pos, SDL_Point* rotPoint = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static void RenderRect(SDL_Rect rect);

	// james functions
	static void SetColor(Colour color);
	/*static void DrawCircle(Transform2D transform, float radius, float lineThickness = 1.0f, int precision = 100);
	static void DrawRect(Transform2D transform, Vec2D dimensions, bool isFilled = false);
	static void DrawLine(Transform2D transform, Vec2D dimensions);*/
	static void DrawText(const char* text, float x, float y, int width, int height);
	static void DrawText(const char* text, float x, float y, int width, int height, int r, int g, int b);

private:
	static SDL_Window* window;
	static TTF_Font* font;
};

