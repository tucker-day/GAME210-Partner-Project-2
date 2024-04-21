#include "GameObject.h"

#include "Graphics.h"

GameObject::GameObject(_Sprite* s, _Body b, _Transform t, int f, bool v)
	: sprite(s), body(b), transform(t), visable(v), animator(_Animator(f)) 
{
	setRotPoint(0.5, 0.5);
}

void GameObject::play(const char* key, bool override)
{
	// call the play function of the animator
	animator.play(key, override);
}

void GameObject::render()
{
	if (visable)
	{
		// get the frame's position of the x and y axis
		int frameX = animator.getFrame() % sprite->numSpritesX;
		int frameY = (int)(floor((float)animator.getFrame() / sprite->numSpritesX)) % sprite->numSpritesY;

		// get the position of the correct frame
		frameX *= sprite->frameWidth;
		frameY *= sprite->frameHeight;

		// create a rect
		SDL_Rect frame = { frameX, frameY, sprite->frameWidth, sprite->frameHeight };

		// call the renderer
		Graphics::RenderGameObject(sprite->texture.texture, &frame, &transform, &rotPoint, (flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, followCamera);
	}
}

void GameObject::update()
{
	// move the body to the game objects position
	body.moveTo(transform);

	// update the animator
	animator.update();
}
