#include "Tile.h"
#include "TextureLoader.h"


Tile::Tile(int pX, int pY, int pWidth, int pHeight, SDL_Texture* ptexture)
{
	_texture = ptexture;
	_rect = SDL_Rect();
	_rect.x = pX;
	_rect.y = pY;
	_rect.w = pWidth;
	_rect.h = pHeight;
}


Tile::~Tile()
{
}



void Tile::render(SDL_Renderer * pRenderer)
{
	SDL_RenderCopy(pRenderer, _texture, NULL, &_rect);
}