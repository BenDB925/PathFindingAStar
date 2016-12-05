#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Entity.h"

class Tile : public Entity
{
public:
	Tile(int pX, int pY, int pWidth, int pHeight, bool pIsPassable);
	~Tile();
	void initTexture(SDL_Texture * groundTexture, SDL_Texture * wallTexture);

	bool _isPassable;
};

