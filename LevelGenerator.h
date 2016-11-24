#pragma once
#include <vector>
#include "Tile.h"
#include <iostream>
#include <string>

class LevelGenerator
{
public:

	//generates 18 walls, 4 of which touches the edge
	static void GenerateMillion(std::vector<std::vector<Tile>> * pMap)
	{
		int endPoint = 990;

		for (int i = 1; i < 19; i++)
		{
			//std::cout << "i: " << std::to_string(50 + (i * 50)) << std::endl;
			endPoint = 990;
			for (int j = 10; j < endPoint; j++)
			{
				if(i % 4 == 0 && j == 10)
				{
					std::cout << "touche wall: " << std::to_string(i) << std::endl;
					endPoint = Game::_WORLD_WIDTH;
				}
				if (i % 4 != 0 && j == 10)
					std::cout << "non touche wall: " << std::to_string(i) << std::endl;

				pMap->at(50 + (i * 50)).at(j)._isPassable = false;
			}
		}
	}
};
