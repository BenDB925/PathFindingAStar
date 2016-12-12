#pragma once
#include "Vector2i.h"
#include <vector>
#include "Tile.h"


using namespace std;

class Job
{
public:
	Job(Vector2i pStart, Vector2i pEnd, vector<vector<Tile>> * pTileMap, int pIndex);
	~Job();

	void execute() const;

private:
	Vector2i _start;
	Vector2i _end;
	vector<vector<Tile>> * _tileMap;
	int _index;
};

