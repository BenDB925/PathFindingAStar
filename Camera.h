#pragma once
#include <SDL.h>

class Camera
{
public:
	Camera() {};
	Camera(int pTileSize, SDL_Point pPos, int pScreenWidth);
	~Camera();
	int findLeftTileIndex() const;
	int findTopTileIndex() const;
	static SDL_Point worldToScreen(SDL_Point pPos);
	
	int _tilesPerScreen;
	static SDL_Point _position;
	

private:
	int _tileSize;
};

