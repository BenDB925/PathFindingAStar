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
	if (_worldPos.y > Game::_WORLD_WIDTH * 0.75 * Game::_TILE_SIZE || _worldPos.y < Game::_WORLD_WIDTH * 0.1 * Game::_TILE_SIZE)
		_DIST_TO_MOVE *= -1;

	_worldPos.y += _DIST_TO_MOVE * pDT;
}
