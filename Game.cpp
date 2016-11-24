#include "Game.h"
#include <iostream>
#include <thread>
#include "TextureLoader.h"


using namespace std;

const float Game::_camSpeed = 0.1f;

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

	SDL_Point camPos;
	camPos.x = 0;
	camPos.y = 0;

	_cam = Camera(_TILE_SIZE, camPos, width);

	return true;
}



void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");


	SDL_Texture* groundTexture = TextureLoader::loadTexture("assets/ground.jpg", m_p_Renderer);


	for (int i = 0; i < _WORLD_WIDTH; i++)
	{
		_tiles.push_back(std::vector<Tile>());

		for (int j = 0; j < _WORLD_WIDTH; j++)
		{
			_tiles[i].push_back(Tile(i * _TILE_SIZE * 1.05, j * _TILE_SIZE * 1.05, _TILE_SIZE, _TILE_SIZE, groundTexture));
		}
	}

	//m_p_Surface = IMG_Load("assets/sprite.png");
	//m_p_Texture = SDL_CreateTextureFromSurface(m_p_Renderer, m_p_Surface);
	//SDL_FreeSurface(m_p_Surface);

	//if(SDL_QueryTexture(m_p_Texture, NULL, NULL, &m_Source.w, &m_Destination.h)==0)
	//{
	//	m_Destination.x = m_Source.x = 0;
	//	m_Destination.y = m_Source.y = 0;
	//	m_Destination.w = m_Source.w;
	//	m_Destination.h = m_Source.h;

	//	//DEBUG_MSG("Destination X:" + m_Destination.x);
	//	/*DEBUG_MSG("Destination Y:" + m_Destination.y);
	//	DEBUG_MSG("Destination W:" + m_Destination.w);
	//	DEBUG_MSG("Destination H:" + m_Destination.h);*/
	//}
	//else
	//{
	//	DEBUG_MSG("Texture Query Failed");
	//	m_running = false;
	//}
}

void Game::Render()
{
	SDL_RenderClear(m_p_Renderer);



	int leftTileIndex = _cam.findLeftTileIndex();
	int topTileIndex = _cam.findTopTileIndex();

	for(int i = leftTileIndex; i < leftTileIndex + _cam._tilesPerScreen; i++)
	{
		for(int j = topTileIndex; j < topTileIndex + _cam._tilesPerScreen; j++)
		{
			_tiles[i][j].render(m_p_Renderer);
		}
	}


	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	//DEBUG_MSG("Updating....");
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
					DEBUG_MSG("Up Key Pressed");
					Camera::_position.y -= _camSpeed;
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					Camera::_position.y += _camSpeed;
					break;
				case SDLK_LEFT:
					DEBUG_MSG("Left Key Pressed");
					SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 255, 255);
					break;
				case SDLK_RIGHT:
					DEBUG_MSG("Right Key Pressed");
					SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
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
	//delete(m_p_Texture);
	//m_p_Texture = NULL;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}