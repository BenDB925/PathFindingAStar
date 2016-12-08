#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Entity.h"
#include "PathFinder.h"

class Enemy : public Entity
{
public:
	Enemy(Vector2 pPos, Vector2 pSize, SDL_Texture * pEnemyTexture);
	~Enemy();

	void Update(double dt);

	void SetPath(vector<Node *> pPath);

private:

	void FollowPath(double dt);

	vector<Vector2> * _path;
	const float _SPEED = 0.15f;
};

