#include "Graphics.h"

SDL_Window* Graphics::window;
SDL_Renderer* Graphics::renderer;
TTF_Font* Graphics::font;

int Graphics::cameraX;
int Graphics::cameraY;
bool Graphics::inFullscreen;

bool Graphics::Init()
{
	// create little window with minimize and x to close 
	window = SDL_CreateWindow("Partner Project 1",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!window)
	{
		return false;
	}

	// fill in that window with a virtual canvas to draw on called a renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		return false;
	}

	// set up the renderer so that the game logic scales with resolution
	SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

	// start text systems
	TTF_Init();
	font = TTF_OpenFont("arialbd.ttf", 24);

	// init the camera position
	cameraX = 0;
	cameraY = 0;

	// make loading message
	StartRender();
	DrawText("Loading...", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 25, 200, 50);
	EndRender();

	return true;
}

void Graphics::StartRender()
{
	// clear the screen color
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0xFF);
}

void Graphics::SetColor(Colour color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
}

void Graphics::EndRender() 
{
	SDL_RenderPresent(renderer);
}

void Graphics::ToggleFullscreen()
{
	SDL_SetWindowFullscreen(window, (!inFullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	inFullscreen = !inFullscreen;
}

void Graphics::SetFullscreen(bool fs)
{
	inFullscreen = fs;
	SDL_SetWindowFullscreen(window, (!inFullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

// example based on the code from: https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
void Graphics::DrawText(const char * text, float x, float y, int width, int height)
{
	DrawText(text, x, y, width, height, 255, 255, 255);
}

void Graphics::DrawText(const char* text, float x, float y, int width, int height, int r, int g, int b)
{
	SDL_Color color = { r, g, b };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = width;
	Message_rect.h = height;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

_Texture Graphics::CreateTexture(const char* file)
{
	// CODE IS BASED OFF YASH'S SDL TEMPLATE
	SDL_Surface* temp;

	try
	{
		// load the file
		temp = SDL_LoadBMP(file);

		// if the file dosen't exist, throw an exception
		if (temp == nullptr)
		{
			throw("Couldn't create texture");
		}

		// make hot pink pixels transparent
		if (SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255)) == -1)
		{
			throw("Couldn't create texture");
		}

		// create texture from the surface
		SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, temp);
		if (SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255)) == -1)
		{
			throw("Couldn't create texture");
		}

		// if texture couldn't be created, throw an exception
		if (!_texture)
		{
			throw("Couldn't create texture");
		}

		// create a texture struct to return
		_Texture result = { _texture, temp->w, temp->h };

		// free the surface
		SDL_FreeSurface(temp);

		return result;
	}
	catch (...)
	{
		// free the previous surface
		SDL_FreeSurface(temp);

		// load the error file
		temp = SDL_LoadBMP("error.bmp");

		// create texture from the surface
		SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, temp);

		// create a texture struct to return
		_Texture result = { _texture, temp->w, temp->h };

		// free the surface
		SDL_FreeSurface(temp);

		return result;
	}
}

_Texture Graphics::CreateText(const char* text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	_Texture temp = {texture, surface->w, surface->h};

	SDL_FreeSurface(surface);

	return temp;
}

void Graphics::MoveCamera(int x, int y)
{
	cameraX += x;
	cameraY += y;
}

void Graphics::MoveCameraTo(int x, int y, bool centered)
{
	cameraX = x - ((centered) ? WINDOW_WIDTH / 2 : 0);
	cameraY = y - ((centered) ? WINDOW_HEIGHT / 2 : 0);
}

void Graphics::MoveCameraTo(SDL_Rect rect, bool centered)
{
	int x = rect.x + ((centered) ? rect.w / 2 : 0);
	int y = rect.y + ((centered) ? rect.h / 2 : 0);

	cameraX = x - ((centered) ? WINDOW_WIDTH / 2 : 0);
	cameraY = y - ((centered) ? WINDOW_HEIGHT / 2 : 0);
}

void Graphics::RenderGameObject(SDL_Texture* texture, SDL_Rect* src, _Transform* pos, SDL_Point* rotPoint, SDL_RendererFlip flip, bool followCamera)
{
	if (followCamera)
	{
		// check if on screen
		SDL_Rect view = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
		if (SDL_HasIntersection(pos, &view))
		{
			SDL_RenderCopyEx(renderer, texture, src, pos, pos->rot, rotPoint, flip);
		}
	}
	else
	{
		// move to correct camera position
		_Transform temp = *pos;
		temp.x -= cameraX;
		temp.y -= cameraY;

		// check if on screen
		SDL_Rect view = { cameraX, cameraY, WINDOW_WIDTH, WINDOW_HEIGHT };
		if (SDL_HasIntersection(pos, &view))
		{
			SDL_RenderCopyEx(renderer, texture, src, &temp, pos->rot, rotPoint, flip);
		}
	}
}

void Graphics::RenderRect(SDL_Rect rect, bool followCamera)
{
	if (followCamera)
	{
		SDL_RenderDrawRect(renderer, &rect);
	}
	else
	{
		SDL_Rect temp = rect;
		temp.x -= cameraX;
		temp.y -= cameraY;

		SDL_RenderDrawRect(renderer, &temp);
	}
}
