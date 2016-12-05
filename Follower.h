#pragma once
#include <vector>
#include "Vector2.h"
#include "Node.h"

using namespace std;

class Follower
{
public:
	Follower();
	~Follower();

	vector<Node *> FindPathToIndex(Vector2i pGoal);

	void SetStartingPos(Vector2i pPos);

private:
	int CalculateHeuristic(Vector2i pPosInGrid, Vector2i pGoal);
	vector<Node *> FindPath(Node* pStartingNode);
	vector<Node *> FindNeighbours(Node * pParentNode, map<int, Node *> * pMap);

	Vector2i _positionInGrid;
	float _heuristicModifier = 2;
	
};
