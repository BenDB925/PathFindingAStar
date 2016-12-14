#pragma once
#include <vector>
#include "Tile.h"

class LevelGenerator
{
public:

	static void GenerateWalls(std::vector<std::vector<Tile>> * pMap, std::vector<Vector2i>  * pWaypoints, int pNumWalls, int pSpaceBetweenWalls)
	{
		int endPoint = Game::_WORLD_WIDTH - 10;
		int startPoint = 0;

		srand(time(nullptr));

		int randomDist = (rand() % 2) - 1 + pSpaceBetweenWalls;

		for (int i = 1; i < pNumWalls; i++)
		{
			if (i % 2 == 0)
			{
				endPoint = Game::_WORLD_WIDTH;
				startPoint = 10;
				pWaypoints->push_back(Vector2i(randomDist + (i * randomDist), 5));
			}
			else
			{
				endPoint = Game::_WORLD_WIDTH - 10;
				startPoint = 0;
				pWaypoints->push_back(Vector2i(randomDist + (i * randomDist), Game::_WORLD_WIDTH - 5));
			}

			for (int j = startPoint; j < endPoint; j++)
			{
				pMap->at(randomDist + (i * randomDist)).at(j)._isPassable = false;
			}
		}
	}
};
