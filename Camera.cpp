#include "Camera.h"

float Camera::_xPos;
float Camera::_yPos;

Camera::Camera(int pTileSize, float pX, float pY, int pScreenWidth)
	:_tileSize(pTileSize)
{
	_xPos = pX;
	_yPos = pY;
	_tilesPerScreen = pScreenWidth / pTileSize + 2;
}


Camera::~Camera()
{
}

int Camera::findLeftTileIndex() const
{
	int remainder = static_cast<int>(_xPos) % _tileSize;
	int leftTilePos = _xPos - remainder;

	return leftTilePos / _tileSize;
}

int Camera::findTopTileIndex() const
{
	int remainder = static_cast<int>(_yPos) % _tileSize;
	int topTilePos = _yPos - remainder;

	return topTilePos / _tileSize;
}

SDL_Point Camera::worldToScreen(SDL_Point pPos)
{
	SDL_Point scrPos;
	scrPos.x = pPos.x - _xPos;
	scrPos.y = pPos.y - _yPos;

	return scrPos;
}
