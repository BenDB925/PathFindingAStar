#include "Game.h"
#include <iostream>
#include <thread>
#include "TextureLoader.h"
#include "LevelGenerator.h"
#include "Enemy.h"
#include "Debug.h"

using namespace std;

Game * Game::_instance;
const float Game::_camSpeed = 150;
vector<vector<Tile>> Game::_tiles;
int Game::_NUM_ENEMIES;

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
double deltaTime = 0;

Game::Game() : m_running(false)
{
	_frameCounter = FramerateCounter();
	_instance = this;
	_threadPool = ThreadPool();
	_followCam = false;
}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_p_Window != 0)
		{
			DEBUG_MSG("Window creation success");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if (m_p_Renderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
			}
			else
			{
				DEBUG_MSG("Renderer init fail");
				return false;
			}
		}
		else
		{
			DEBUG_MSG("Window init fail");
			return false;
		}
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}

	_hasPathFound = false;
	m_running = true;

	_cam = Camera(_TILE_SIZE, 0, 0, width);

	_enemies = vector<Enemy>();

	Vector2 basePos = Vector2(_TILE_SIZE * 960, _TILE_SIZE * 100);
	_enemTexture = TextureLoader::loadTexture("assets/slime.jpg", m_p_Renderer);

	for (int i = 0; i < _WORLD_WIDTH; i++)
	{
		_tiles.push_back(vector<Tile>());

		for (int j = 0; j < _WORLD_WIDTH; j++)
		{
			_tiles[i].push_back(Tile(i * _TILE_SIZE, j * _TILE_SIZE, _TILE_SIZE, _TILE_SIZE, true));
		}
	}

	_waypoints = vector<Vector2i>();

	if (_WORLD_WIDTH == 30)
	{
		_NUM_ENEMIES = 50;
		LevelGenerator::GenerateWalls(&_tiles, &_waypoints, 2, 10);
	}
	else if (_WORLD_WIDTH == 100)
	{
		_NUM_ENEMIES = 100;
		LevelGenerator::GenerateWalls(&_tiles, &_waypoints, 9, 10);
	}
	else if (_WORLD_WIDTH == 1000)
	{
		_NUM_ENEMIES = 500;
		LevelGenerator::GenerateWalls(&_tiles, &_waypoints, 19, 50);
	}

	Vector2 rectSize = Vector2(_TILE_SIZE / 2, _TILE_SIZE / 2);
	for (int i = 0; i < _NUM_ENEMIES; i++)
	{
		Vector2i position = Vector2i(_WORLD_WIDTH - 2, 0 + (i / 2));//Vector2(((float)(rand() % 1000) / 1000) * rectSize.x + basePos.x, ((float)(rand() % 1000) / 1000) * rectSize.y + basePos.y);

		_enemies.push_back(Enemy(position, rectSize, _enemTexture, _waypoints.size(), i));
	}

	_player = new Player(Vector2i(1, 1), rectSize, _enemTexture);

	return true;
}


void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");

	_groundTexture = TextureLoader::loadTexture("assets/ground.png", m_p_Renderer);
	_wallTexture = TextureLoader::loadTexture("assets/wall.png", m_p_Renderer);

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles.at(i).size(); j++)
		{
			_tiles.at(i).at(j).initTexture(_groundTexture, _wallTexture);
		}
	}

}

void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);

	int leftTileIndex = _cam.findLeftTileIndex();
	if (leftTileIndex < 0)
		leftTileIndex = 0;
	if (leftTileIndex > _WORLD_WIDTH - _cam._tilesPerScreen - 1)
		leftTileIndex = _WORLD_WIDTH - _cam._tilesPerScreen - 1;

	int topTileIndex = _cam.findTopTileIndex();
	if (topTileIndex < 0)
		topTileIndex = 0;
	if (topTileIndex > _WORLD_WIDTH - _cam._tilesPerScreen - 1)
		topTileIndex = _WORLD_WIDTH - _cam._tilesPerScreen - 1;

	for (int i = leftTileIndex; i < leftTileIndex + _cam._tilesPerScreen; i++)
	{
		for (int j = topTileIndex; j < topTileIndex + _cam._tilesPerScreen; j++)
		{
			if (i > -1 && j > -1)
				_tiles[i][j].render(m_p_Renderer);
		}
	}

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].render(m_p_Renderer);
	}

	_player->render(m_p_Renderer);

	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	Uint64 temp = SDL_GetPerformanceFrequency();

	deltaTime = (static_cast<double>((NOW - LAST) * 500.0) / static_cast<double>(temp));
	deltaTime /= 1.0f;

	if (deltaTime > 5)
		deltaTime = 5;
	//_frameCounter.update(m_p_Renderer);

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].Update(deltaTime);
	}

	if (_followCam == true)
	{
		Camera::_xPos = _enemies[0]._worldPos.x - (_cam._tilesPerScreen * _TILE_SIZE / 2); //497 fucked
		Camera::_yPos = _enemies[0]._worldPos.y - (_cam._tilesPerScreen * _TILE_SIZE / 3);
	}

	_player->Update(deltaTime);
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_running = false;
					break;
				case SDLK_UP:
					Camera::_yPos -= _camSpeed;
					break;
				case SDLK_DOWN:
					Camera::_yPos += _camSpeed;
					break;
				case SDLK_LEFT:
					Camera::_xPos -= _camSpeed;
					break;
				case SDLK_RIGHT:
					Camera::_xPos += _camSpeed;
					break;
				case SDLK_SPACE:
					if (_hasPathFound == false)
					{
						for (int i = 0; i < _NUM_ENEMIES; i++)
						{
							AddNewWaypointForEnems(i);
							_enemies.at(i)._hasAskedForPath = true;
						}
					}
					break;
				case SDLK_f:
					_followCam = !_followCam;
					break;
				default:
					break;
				}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::UnloadContent()
{
	DEBUG_MSG("Unloading Content");
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}

void Game::UpdateEnemPath(int pIndex, vector<Node*>* pPath)
{
	_enemies.at(pIndex).SetPath(*pPath); 
}

void Game::AddNewWaypointForEnems(int pEnemyIndex)
{

	_enemies[pEnemyIndex]._indexOfWaypoint--;
	Vector2i positionInMap;

	if (_enemies[pEnemyIndex]._indexOfWaypoint == _waypoints.size() - 1)
	{
		positionInMap = Vector2i(_enemies[pEnemyIndex]._worldPos.x / _TILE_SIZE, _enemies[pEnemyIndex]._worldPos.y / _TILE_SIZE);
	}
	else
	{
		positionInMap = _waypoints[_enemies[pEnemyIndex]._indexOfWaypoint + 1];
	}

	Job *job = new Job(positionInMap, _waypoints[_enemies[pEnemyIndex]._indexOfWaypoint], &_tiles, pEnemyIndex);
	PathFinder::instance();
	_threadPool.addJob(job);
}

void Game::SetPathToPlayer(int pEnemyIndex)
{
	Vector2i positionInMap;

	positionInMap = Vector2i(_enemies[pEnemyIndex]._worldPos.x / _TILE_SIZE, _enemies[pEnemyIndex]._worldPos.y / _TILE_SIZE);
	Vector2i playerPos = Vector2i(_player->_worldPos.x / _TILE_SIZE, _player->_worldPos.y / _TILE_SIZE);;

	Job *job = new Job(positionInMap, playerPos, &_tiles, pEnemyIndex);
	PathFinder::instance();
	_threadPool.addJob(job);
}

void Game::AddEnemyJobToThread(int pEnemyIndex)
{
	if (_enemies[pEnemyIndex]._indexOfWaypoint >= 0)
	{
		AddNewWaypointForEnems(pEnemyIndex);
	}
	else
	{
		SetPathToPlayer(pEnemyIndex);
	}
}