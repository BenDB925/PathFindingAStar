#include "Game.h"
#include <iostream>
#include <thread>
#include "TextureLoader.h"
#include "LevelGenerator.h"
#include "Enemy.h"
#include "Debug.h"


using namespace std;

const float Game::_camSpeed = 250;
vector<vector<Tile>> Game::_tiles;

Game::Game() : m_running(false)
{
	_frameCounter = FramerateCounter();
}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_p_Window != 0)
		{
			DEBUG_MSG("Window creation success");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
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

	m_running = true;

	_cam = Camera(_TILE_SIZE, 0,0, width);

	_enemies = vector<Enemy>();

	Vector2 basePos = Vector2(_TILE_SIZE * 960, _TILE_SIZE * 100);
	Vector2 rectSize = Vector2(_TILE_SIZE * 25, _TILE_SIZE * 500);
	_enemTexture = TextureLoader::loadTexture("assets/slime.jpg", m_p_Renderer);

	for(int i = 0; i < 500; i++)
	{
		//Vector2 pPos, Vector2 pSize, SDL_Texture * pEnemyTexture)
		Vector2 position = Vector2(((float)(rand() % 1000) / 1000) * rectSize.x + basePos.x, ((float)(rand() % 1000) / 1000) * rectSize.y + basePos.y);
		Vector2 rectSize = Vector2(_TILE_SIZE / 2, _TILE_SIZE / 2);

		_enemies.push_back(Enemy(position, rectSize, _enemTexture));
		_enemies[i].SetStartingPos(Vector2i(50, 200));
	}
	return true;
}


void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");

	for (int i = 0; i < _WORLD_WIDTH; i++)
	{
		_tiles.push_back(vector<Tile>());

		for (int j = 0; j < _WORLD_WIDTH; j++)
		{
			_tiles[i].push_back(Tile(i * _TILE_SIZE, j * _TILE_SIZE, _TILE_SIZE, _TILE_SIZE, true));
		}
	}

	LevelGenerator::GenerateMillion(&_tiles);

	_groundTexture = TextureLoader::loadTexture("assets/ground.png", m_p_Renderer);
	_wallTexture = TextureLoader::loadTexture("assets/wall.png", m_p_Renderer);

	for(int i = 0; i < _tiles.size(); i++)
	{
		for(int j = 0; j < _tiles.at(i).size(); j ++)
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
			_tiles[i][j].render(m_p_Renderer);
		}
	}

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].render(m_p_Renderer);
	}

	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	for(int i = 0; i < _enemies.size(); i++)
	{
		//_enemies[i].FindPathToIndex(Vector2i(0, 0));
	}

	_frameCounter.update(m_p_Renderer);
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
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