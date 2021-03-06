#include "PathFinder.h"
#include <algorithm>
#include "Game.h" 

PathFinder * PathFinder::_instance;

PathFinder::PathFinder()
{
}

PathFinder * PathFinder::instance()
{
	if(_instance == nullptr)
	{
		_instance = new PathFinder();
	}

	return _instance;
}

PathFinder::~PathFinder()
{
}

Node * GetNodeInMap(map<int, Node *> * pNodeMap, Vector2i pPos)
{
	int key = (pPos.y * Game::_WORLD_WIDTH) + pPos.x;

	if (pNodeMap->find(key) == pNodeMap->end())
	{
		Node * node = new Node();
		node->_posInGrid = pPos;
		pNodeMap->insert(make_pair(key, node));
	}

	return pNodeMap->at(key);
}

vector<Node> PathFinder::FindPathToIndex(Vector2i pPos, Vector2i pGoal, vector<vector<Tile>> * pTileMap)
{
	_positionInGrid = pPos;

	map<int, Node *> nodeMap = map<int, Node *>();

	//the list of nodes we still have to check out
	vector<Node*> openList = vector<Node*>();
	//the list of nodes we have checked
	vector<Node*> closedList = vector<Node*>();

	//find variables of starting tile	
	Node * node = GetNodeInMap(&nodeMap, _positionInGrid);
	node->_g = 0;
	node->_h = CalculateHeuristic(node->_posInGrid, pGoal);
	node->_f = node->_g + node->_h;
	openList.push_back(node);

	while (openList.size() != 0)
	{
		Node * currNode;

		for (int i = 0; i < openList.size(); i++)
		{
			currNode = openList[i];
			currNode->_h = CalculateHeuristic(currNode->_posInGrid, pGoal);
			currNode->_f = currNode->_g + (currNode->_h * _heuristicModifier);
		}

		int indexOfLowestF = -1;
		int lowestF = 99999999;
		for (int i = 0; i < openList.size(); i++)
		{
			//find the closest node
			if (openList[i]->_f < lowestF)
			{
				lowestF = openList[i]->_f;
				indexOfLowestF = i;
			}
		}

		//set current to the closest node
		Node * current = openList[indexOfLowestF];
		//if the goal
		if (current == GetNodeInMap(&nodeMap, pGoal))
		{
			return FindPath(current, nodeMap);
		}

		//remove current
		openList.erase(openList.begin() + indexOfLowestF);
		closedList.push_back(current);

		vector<Node*> neighbours = FindNeighbours(current, &nodeMap, pTileMap);

		for (int i = 0; i < neighbours.size(); i++)
		{
			Node * currNeighbour = neighbours.at(i);

			//if current is not in closedList
			if (find(closedList.begin(), closedList.end(), currNeighbour) == closedList.end())
			{
				currNeighbour->_h = CalculateHeuristic(currNeighbour->_posInGrid, pGoal);
				currNeighbour->_f = currNeighbour->_g + currNeighbour->_h;

				if (find(openList.begin(), openList.end(), currNeighbour) == openList.end())
				{
					openList.push_back(currNeighbour);
				}
				else
				{
					Node * comparerNode;
 					for (int j = 0; j < neighbours.size(); j++)
					{
						comparerNode = neighbours.at(j);
						if (comparerNode->_g < currNeighbour->_g && comparerNode->_parentNode != currNeighbour)
						{
							currNeighbour->_g = comparerNode->_g;
							currNeighbour->_parentNode = comparerNode;
						}
					}
				}
			}
		}
	}

	map<int, Node *>::iterator it = nodeMap.begin();
	if (it != nodeMap.end())
	{
		delete it->second;
		nodeMap.erase(it);
	}
	//no path found
	return vector<Node>();
}

int PathFinder::CalculateHeuristic(Vector2i pPosInGrid, Vector2i pGoal)
{
	int xDiff = max(pPosInGrid.x - pGoal.x, pGoal.x - pPosInGrid.x);
	int yDiff = max(pPosInGrid.y - pGoal.y, pGoal.y - pPosInGrid.y);

	//manhattan distance
	return xDiff + yDiff;
}

vector<Node> PathFinder::FindPath(Node* pStartingNode, map<int, Node *> pMap)
{
	vector<Node> path = vector<Node>();

	path.push_back(*pStartingNode);

	Node * currNode = pStartingNode;

	while (currNode->_parentNode != nullptr && path.size() < 3000)
	{
		path.push_back(*currNode->_parentNode);
		currNode = currNode->_parentNode;
	}

	for (map< int, Node* >::iterator it = pMap.begin(); it != pMap.end(); ++it) {
		Node* point = it->second;
		delete point;
	}
	pMap.clear();

	if (path.size() > 1)
		return path;
	else
		return vector<Node>();
}

vector<Node*> PathFinder::FindNeighbours(Node * pParentNode, map<int, Node *> * pMap, vector<vector<Tile>> * pTileMap)
{
	vector<Node *> neighbours = vector<Node *>();
	Vector2i parentIndex = pParentNode->_posInGrid;

	if (pTileMap->at(parentIndex.x).at(parentIndex.y)._isPassable == false)
		return neighbours;

	//check for walls here
	Node * rightNode = GetNodeInMap(pMap, Vector2i(parentIndex.x + 1, parentIndex.y));
	Node * leftNode = GetNodeInMap(pMap, Vector2i(parentIndex.x - 1, parentIndex.y));
	Node * upNode = GetNodeInMap(pMap, Vector2i(parentIndex.x, parentIndex.y + 1));
	Node * downNode = GetNodeInMap(pMap, Vector2i(parentIndex.x, parentIndex.y - 1));

	if (parentIndex.x + 1 < Game::_WORLD_WIDTH && pTileMap->at(parentIndex.x + 1).at(parentIndex.y)._isPassable)
		neighbours.push_back(rightNode);
	if (parentIndex.x - 1 >= 0 && pTileMap->at(parentIndex.x - 1).at(parentIndex.y)._isPassable)
		neighbours.push_back(leftNode);
	if (parentIndex.y + 1 < Game::_WORLD_WIDTH && pTileMap->at(parentIndex.x).at(parentIndex.y + 1)._isPassable)
		neighbours.push_back(upNode);
	if (parentIndex.y - 1 >= 0 && pTileMap->at(parentIndex.x).at(parentIndex.y - 1)._isPassable)
		neighbours.push_back(downNode);

	for (int i = 0; i < neighbours.size(); i++)
	{
		if (neighbours[i]->_parentNode == nullptr && !(neighbours[i]->_posInGrid.x == _positionInGrid.x && neighbours[i]->_posInGrid.y == _positionInGrid.y))
		{
			neighbours[i]->_g = pParentNode->_g + 1;
			neighbours[i]->_parentNode = pParentNode;
		}
	}

	return neighbours;
}
