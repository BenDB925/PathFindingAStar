#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Entity.h"
#include "PathFinder.h"

class Enemy : public Entity
{
public:
	Enemy(Vector2i pPos, Vector2 pSize, SDL_Texture * pEnemyTexture);
	~Enemy();

	void Update(double dt);

	void SetPath(vector<Node *> pPath);

	vector<Vector2> * _path;
private:

	void FollowPath(double dt);

	const float _SPEED = 4.0f;
};

