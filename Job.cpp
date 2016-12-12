#include "Job.h"
#include "PathFinder.h"
#include "Game.h"

Job::Job(Vector2i pStart, Vector2i pEnd, vector<vector<Tile>>* pTileMap, int pIndex)
	:_start(pStart),
	 _end(pEnd),
	 _tileMap(pTileMap),
	 _index(pIndex)
{

}

Job::~Job()
{
}

void Job::execute() const
{
	vector<Node* > path = PathFinder::_instance->FindPathToIndex(_start, _end, _tileMap);
	Game::_instance->UpdateEnemPath(_index, &path);
}
