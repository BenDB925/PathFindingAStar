#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int pX, int pY, int pWidth, int pHeight, bool pIsPassable);
	~Tile();
	void initTexture(SDL_Texture * groundTexture, SDL_Texture * wallTexture);
	void render(SDL_Renderer * pRenderer);

	bool _isPassable;

private:
	SDL_Texture* _texture;
	SDL_Rect _rect;
	SDL_Point _worldPos;
};

