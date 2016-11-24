#include "Camera.h"

SDL_Point Camera::_position;

Camera::Camera(int pTileSize, SDL_Point pPos, int pScreenWidth)
	:_tileSize(pTileSize)
{
	_position = pPos;
	_tilesPerScreen = pScreenWidth / pTileSize + 1;
}


Camera::~Camera()
{
}

int Camera::findLeftTileIndex() const
{
	int remainder = _position.x % _tileSize;
	int leftTilePos = _position.x - remainder;

	return leftTilePos / _tileSize;
}

int Camera::findTopTileIndex() const
{
	int remainder = _position.y % _tileSize;
	int topTilePos = _position.y - remainder;

	return topTilePos / _tileSize;
}

SDL_Point Camera::worldToScreen(SDL_Point pPos)
{
	SDL_Point scrPos;
	scrPos.x = pPos.x - _position.x;
	scrPos.y = pPos.y - _position.y;

	return scrPos;
}
