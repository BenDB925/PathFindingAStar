#include "Tile.h"
#include "TextureLoader.h"
#include "Camera.h"


Tile::Tile(int pX, int pY, int pWidth, int pHeight, SDL_Texture* ptexture)
{
	_texture = ptexture;
	_rect = SDL_Rect();
	_rect.x = pX;
	_rect.y = pY;
	_rect.w = pWidth;
	_rect.h = pHeight;

	_worldPos = SDL_Point();
	_worldPos.x = pX;
	_worldPos.y = pY;
}


Tile::~Tile()
{
}



void Tile::render(SDL_Renderer * pRenderer)
{
	SDL_Point screenPoint = Camera::worldToScreen(_worldPos);

	_rect.x = screenPoint.x;
	_rect.y = screenPoint.y;

	SDL_RenderCopy(pRenderer, _texture, NULL, &_rect);
}
