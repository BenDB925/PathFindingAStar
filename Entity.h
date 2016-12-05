#pragma once
#include "Vector2.h"
#include <SDL.h>

class Entity
{
public:
	Entity();
	~Entity();

	void render(SDL_Renderer * pRenderer);

protected:

	SDL_Texture* _texture;
	SDL_Rect _rect;
	Vector2i _worldPos;
};

