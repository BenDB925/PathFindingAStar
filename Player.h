#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(Vector2i pPos, Vector2 pSize, SDL_Texture * pEnemyTexture);
	~Player();

	void Update(float pDT);

private:
	float _timer;
	const float _TIME_BEFORE_MOVE = 200;
	const float _DIST_TO_MOVE = 1;
};

