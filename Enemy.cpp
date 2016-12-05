#include "Enemy.h"

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
