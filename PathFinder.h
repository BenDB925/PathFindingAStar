#pragma once
#include <vector>
#include "Vector2.h"
#include "Node.h"
#include "Tile.h"

using namespace std;

class PathFinder
{
public:
	static PathFinder * instance();
	~PathFinder();

	vector<Node *> FindPathToIndex(Vector2i pPos, Vector2i pGoal, vector<vector<Tile>> * pTileMap);

	static PathFinder * _instance;
private:
	PathFinder();
	int CalculateHeuristic(Vector2i pPosInGrid, Vector2i pGoal);
	vector<Node *> FindPath(Node* pStartingNode);
	vector<Node *> FindNeighbours(Node * pParentNode, map<int, Node *> * pMap, vector<vector<Tile>> * pTileMap);

	Vector2i _positionInGrid;
	float _heuristicModifier = 2;
};
