#include "Entity.h"
#include "Camera.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::render(SDL_Renderer * pRenderer)
{
	Vector2i screenPoint = Camera::worldToScreen(_worldPos);

	_rect.x = screenPoint.x;
	_rect.y = screenPoint.y;

	SDL_RenderCopy(pRenderer, _texture, NULL, &_rect);
}