#include "GameObject.h"

#include "Graphics.h"

GameObject::GameObject(_Sprite* s, _Body b, _Transform t, int f, bool v)
	: sprite(s), body(b), transform(t), visable(v), animator(_Animator(f)) {}

void GameObject::play(const char* key)
{
	// call the play function of the animator
	animator.play(key);
}

void GameObject::render()
{
	if (visable)
	{
		// create an sdl rect to display the correct frame
		int frameX = animator.getFrame() % sprite->numSpritesX;
		int frameY = (int)(floor((float)animator.getFrame() / sprite->numSpritesX)) % sprite->numSpritesY;

		frameX *= sprite->frameWidth;
		frameY *= sprite->frameHeight;

		SDL_Rect frame = { frameX, frameY, sprite->frameWidth, sprite->frameHeight };

		Graphics::RenderGameObject(sprite->texture.texture, &frame, &transform);
	}

	if (Graphics::RENDER_BODIES)
	{
		Graphics::RenderRect(body.getRect());
	}
}

void GameObject::update()
{
	// move the body to the game objects position
	body.moveTo(transform);

	// update the animator
	animator.update();
}