#pragma once
#include "Vector2.h"
#include <SDL.h>

class Entity
{
public:
	Entity();
	~Entity();

	void render(SDL_Renderer * pRenderer);

	Vector2 _worldPos;
protected:

	//Vector2i _worldPos;
	SDL_Texture* _texture;
	SDL_Rect _rect;
};

