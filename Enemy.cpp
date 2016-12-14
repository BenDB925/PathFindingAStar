#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Vector2i pGridPos, Vector2 pSize, SDL_Texture * pEnemyTexture, int pIndexOfWaypoint)
{
	_indexOfWaypoint = pIndexOfWaypoint;
	_worldPos.x = pGridPos.x * Game::_TILE_SIZE;
	_worldPos.y = pGridPos.y * Game::_TILE_SIZE;

	_texture = pEnemyTexture;
	_rect.x = _worldPos.x;
	_rect.y = _worldPos.y;
	_rect.w = pSize.x;
	_rect.h = pSize.y;
	_path = new vector<Vector2>();
	_sem = SDL_CreateSemaphore(1);
}

Enemy::~Enemy()
{

}

void Enemy::Update(double dt)
{
	SDL_SemWait(_sem);
	if(_path->size() > 0)
	{
		Vector2 dest = _path->at(_path->size() - 1);
		dest = dest - _worldPos;
		float length = dest.Length();

		if(abs(length) > 2000)
		{
			int debug = 0;
		}

		while (abs(length) < 16)
		{
			if (_path->size() == 1)
			{
				_path->pop_back();
				SDL_SemPost(_sem);
				return;
			}
			Vector2 pos = _path->at(_path->size() - 1);
			_path->pop_back();
			dest.x = _worldPos.x - pos.x;
			dest.y = _worldPos.y - pos.y;
			length = dest.Length();
		}
		if(length < 2000)
			FollowPath(dt, dest);
	}
	SDL_SemPost(_sem);
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
	if (_indexOfWaypoint <= 0)
		int j = 0;
	vector<Vector2> * newPath = ChangeToWorldUnits(&pPath);
	SDL_SemWait(_sem);
	if(_path->size() > 0)
	{
		_path->insert(_path->begin(), newPath->begin(), newPath->end());
	}
	else
	{
		_path = newPath;
	}
	SDL_SemPost(_sem);
}

void Enemy::FollowPath(double dt, Vector2 pDest)
{
	Vector2 velocity;
	Vector2 normalised = pDest.Normalize();
	velocity.x = normalised.x * dt * _SPEED;
	velocity.y = normalised.y * dt * _SPEED;

	_worldPos.x = velocity.x + _worldPos.x;
	_worldPos.y = velocity.y + _worldPos.y;
}

