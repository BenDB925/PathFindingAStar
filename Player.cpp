#include "Player.h"
#include "Game.h"


Player::Player(Vector2i pPos, Vector2 pSize, SDL_Texture* pEnemyTexture)
{
	_worldPos.x = pPos.x * Game::_TILE_SIZE;
	_worldPos.y = pPos.y * Game::_TILE_SIZE;

	_texture = pEnemyTexture;
	_rect.x = _worldPos.x;
	_rect.y = _worldPos.y;
	_rect.w = pSize.x;
	_rect.h = pSize.y;
}

Player::~Player()
{
}

void Player::Update(float pDT)
{
	_timer += pDT;

	if(_timer > _TIME_BEFORE_MOVE)
	{
		_timer = 0;
		_worldPos.y += _DIST_TO_MOVE * pDT;
	}
}
