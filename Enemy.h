#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Entity.h"
#include "Follower.h"

class Enemy : public Entity, public Follower
{
public:
	Enemy(Vector2 pPos, Vector2 pSize, SDL_Texture * pEnemyTexture);
	~Enemy();
};

