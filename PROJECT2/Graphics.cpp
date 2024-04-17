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

//void Graphics::DrawRect(Transform2D transform, Vec2D dimensions, bool isFilled)
//{
//	SDL_Rect Bounds;
//	Bounds.x = transform.position.x;
//	Bounds.y = transform.position.y;
//	Bounds.w = dimensions.x;
//	Bounds.h = dimensions.y;
//
//	if (isFilled)
//	{
//		SDL_RenderFillRect(renderer, &Bounds);
//	}
//	else
//	{
//		SDL_RenderDrawRect(renderer, &Bounds);
//	}
//}
//
//void Graphics::DrawCircle(Transform2D transform, float radius, float lineThickness, int precision )
//{
//	// this function essentially draws a whole bunch of lines around a central point to form our circle.
//	const double ANGLE_OFF = 2.0 * M_PI / precision;
//
//	for (int i = 0; i < precision; i++)
//	{
//		double angle1 = ANGLE_OFF * i;
//		double angle2 = ANGLE_OFF * (i + lineThickness*10);
//		int x1 = transform.position.x + (int)(radius * cos(angle1));
//		int y1 = transform.position.y + (int)(radius * sin(angle1));
//		int x2 = transform.position.x + (int)(radius * cos(angle2));
//		int y2 = transform.position.y + (int)(radius * sin(angle2));
//
//		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
//	}
//}
//
//void Graphics::DrawLine(Transform2D transform, Vec2D dimensions)
//{
//	SDL_Rect Bounds;
//	Bounds.x = transform.position.x;
//	Bounds.y = transform.position.y;
//	Bounds.w = dimensions.x;
//	Bounds.h = dimensions.y;
//
//	SDL_RenderDrawLine(renderer, transform.position.x, transform.position.y, dimensions.x, dimensions.y);
//}

void Graphics::EndRender() 
{
	SDL_RenderPresent(renderer);
	// wait 2 frames
	SDL_Delay(2);
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

	// load the file
	temp = SDL_LoadBMP(file);

	// if the file dosen't exist, load the error texture
	if (temp == nullptr)
	{
		temp = SDL_LoadBMP("error.bmp");
	}

	// make hot pink pixels transparent
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255));

	// create texture from the surface
	SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, temp);

	// if texture couldn't be created, throw an exception
	if (!_texture)
	{
		throw("Couldn't create texture: %s", SDL_GetError());
	}

	// create a texture struct to return
	_Texture result = { _texture, temp->w, temp->h };

	// free the surface
	SDL_FreeSurface(temp);
	
	return result;
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
