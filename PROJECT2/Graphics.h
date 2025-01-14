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
	static const bool RENDER_BODIES = false;

	static bool Init();

	static void StartRender();
	static void EndRender();

	static void ToggleFullscreen();
	static void SetFullscreen(bool fullscreen);

	static void Shutdown() { TTF_CloseFont(font); };

	static _Texture CreateTexture(const char* file);
	static _Texture CreateText(const char* text, SDL_Color color);

	static void MoveCamera(int x, int y);
	static void MoveCameraTo(int x, int y, bool centered = true);
	static void MoveCameraTo(SDL_Rect rect, bool centered = true);

	static int cameraX, cameraY;

	static void RenderGameObject(SDL_Texture* texture, SDL_Rect* src, _Transform* pos, SDL_Point* rotPoint = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, bool followCamera = false);
	static void RenderRect(SDL_Rect rect, bool followCamera = false);

	static void DrawText(const char* text, float x, float y, int width, int height);
	static void DrawText(const char* text, float x, float y, int width, int height, int r, int g, int b);

private:
	static bool inFullscreen;

	static SDL_Renderer* renderer;
	static SDL_Window* window;
	static TTF_Font* font;
};

