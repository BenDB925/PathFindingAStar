#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include "Tile.h"
#include <vector>
#include "FramerateCounter.h"
#include "Camera.h"
#include "Enemy.h"
#include "ThreadPool.h"

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
	void LoadContent();
	void UnloadContent();
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();

	void UpdateEnemPath(int pIndex, vector<Node *> * pPath);

	static const int _WORLD_WIDTH = 1000;
	static const int _TILE_SIZE = 16;
	static const int _NUM_ENEMIES = 500;

	static Game * _instance;

private:
	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
	SDL_Surface* m_p_Surface;

	static const float _camSpeed;

	ThreadPool _threadPool;

	static vector<vector<Tile>> _tiles;
	vector<vector<Node*>> _navMesh;

	vector<Enemy> _enemies;

	FramerateCounter _frameCounter;
	Camera _cam;
	SDL_Texture* _groundTexture;
	SDL_Texture* _wallTexture;
	SDL_Texture* _enemTexture;
};
#endif