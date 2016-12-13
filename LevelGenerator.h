#pragma once
#include <vector>
#include "Tile.h"

class LevelGenerator
{
public:

	static void GenerateMillion(std::vector<std::vector<Tile>> * pMap, std::vector<Vector2i>  * pWaypoints)
	{
		int endPoint = 990;
		int startPoint = 0;

		for (int i = 1; i < 19; i++)
		{
			if (i % 2 == 0)
			{
				endPoint = Game::_WORLD_WIDTH;
				startPoint = 10;
				pWaypoints->push_back(Vector2i(50 + (i * 50), 5));
			}
			else
			{
				endPoint = Game::_WORLD_WIDTH - 10;
				startPoint = 0;
				pWaypoints->push_back(Vector2i(50 + (i * 50), Game::_WORLD_WIDTH - 5));
			}

			for (int j = startPoint; j < endPoint; j++)
			{
				pMap->at(50 + (i * 50)).at(j)._isPassable = false;
			}
		}
	}
};
