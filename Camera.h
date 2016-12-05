#pragma once
#include <SDL.h>
#include "Vector2.h"

class Camera
{
public:
	Camera() {};
	Camera(int pTileSize, float pX, float pY, int pScreenWidth);
	~Camera();
	int findLeftTileIndex() const;
	int findTopTileIndex() const;
	static Vector2i worldToScreen(Vector2i pPos);
	
	int _tilesPerScreen;
	static float _xPos;
	static float _yPos;
	

private:
	int _tileSize;
};

