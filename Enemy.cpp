#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Vector2 pPos, Vector2 pSize, SDL_Texture * pEnemyTexture)
{
	_worldPos.x = pPos.x;
	_worldPos.y = pPos.y;

	_texture = pEnemyTexture;
	_rect.x = _worldPos.x;
	_rect.y = _worldPos.y;
	_rect.w = pSize.x;
	_rect.h = pSize.y;
}

Enemy::~Enemy()
{

}

void Enemy::Update(double dt)
{
	if(_path->size() > 0)
	{
		FollowPath(dt);
	}
}

vector<Vector2> * ChangeToWorldUnits(vector<Node*> * pPath)
{
	vector<Vector2> * pathInWorldUnits = new vector<Vector2>();

	for (int i = 0; i < pPath->size(); i++)
	{
		pathInWorldUnits->push_back(Vector2(pPath->at(i)->_posInGrid.x * Game::_TILE_SIZE, pPath->at(i)->_posInGrid.y * Game::_TILE_SIZE));
	}
	return pathInWorldUnits;
} 

void Enemy::SetPath(vector<Node*> pPath)
{
	_path = ChangeToWorldUnits(&pPath);
}

void Enemy::FollowPath(double dt)
{
	Vector2 dest = _path->at(_path->size() - 1) - _worldPos;
	float length = dest.Length();
	while(length < 20)
	{
		if (_path->size() == 1)
		{
			_path->pop_back();
			return;
		}

		_path->pop_back();
		dest.x = _worldPos.x - _path->at(_path->size() - 1).x;
		dest.y = _worldPos.y - _path->at(_path->size() - 1).y;
		length = dest.Length();
	}

	Vector2 velocity;
	Vector2 normalised = dest.Normalize();
	velocity.x = normalised.x * dt * _SPEED;
	velocity.y = normalised.y * dt * _SPEED;

	_worldPos.x = velocity.x + _worldPos.x;
	_worldPos.y = velocity.y + _worldPos.y;
}

