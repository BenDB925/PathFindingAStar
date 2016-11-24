#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int pX, int pY, int pWidth, int pHeight, SDL_Texture* ptexture);
	~Tile();

	void render(SDL_Renderer * pRenderer);

private:
	SDL_Texture* _texture;
	SDL_Rect _rect;
};

