#pragma once
#include <vector>
#include "Vector2.h"
#include "Node.h"

class Follower
{
public:
	Follower();
	~Follower();

	std::vector<Node *> FindPathToIndex(Vector2i pGoal);

	void SetStartingPos(Vector2i pPos);

private:
	int CalculateHeuristic(Vector2i pPosInGrid, Vector2i pGoal);
	std::vector<Node *> FindPath(Node* pStartingNode);
	std::vector<Node *> FindNeighbours(Node * pParentNode, std::map<int, Node *> * pMap);

	Vector2i _positionInGrid;
	int _threadID;
	float _heuristicModifier = 2;
};
