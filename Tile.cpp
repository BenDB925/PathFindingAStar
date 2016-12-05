#include "Tile.h"
#include "TextureLoader.h"
#include "Vector2.h"


Tile::Tile(int pX, int pY, int pWidth, int pHeight, bool pIsPassable)
{
	_isPassable = pIsPassable;

	_rect = SDL_Rect();
	_rect.x = pX;
	_rect.y = pY;
	_rect.w = pWidth;
	_rect.h = pHeight;

	_worldPos = Vector2i(pX, pY);
}


Tile::~Tile()
{

}

void Tile::initTexture(SDL_Texture * pGroundTexture, SDL_Texture * pWallTexture)
{
	if (_isPassable == true)
		_texture = pGroundTexture;
	else
		_texture = pWallTexture;
}
