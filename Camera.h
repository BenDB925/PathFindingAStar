#pragma once
#include <SDL.h>

class Camera
{
public:
	Camera() {};
	Camera(int pTileSize, float pX, float pY, int pScreenWidth);
	~Camera();
	int findLeftTileIndex() const;
	int findTopTileIndex() const;
	static SDL_Point worldToScreen(SDL_Point pPos);
	
	int _tilesPerScreen;
	static float _xPos;
	static float _yPos;
	

private:
	int _tileSize;
};

