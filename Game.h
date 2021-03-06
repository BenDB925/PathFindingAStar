#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include "Tile.h"
#include <vector>
#include "Camera.h"
#include "Enemy.h"
#include "ThreadPool.h"
#include "Player.h"

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

	void UpdateEnemPath(int pIndex, vector<Node> * pPath);
	void AddEnemyJobToThread(int pEnemyIndex);

	static const int _WORLD_WIDTH = 1000;
	static const int _TILE_SIZE = 16;
	static int _NUM_ENEMIES;

	static Game * _instance;

	bool _useThreads;

private:

	void AddNewWaypointForEnems(int pEnemyIndex);
	void SetPathToPlayer(int pEnemyIndex);
	void Reset();

	int _windowWidth;
	bool m_running;
	bool _hasPathFound;
	bool _followCam;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
	SDL_Surface* m_p_Surface;

	static const float _camSpeed;
	ThreadPool _threadPool;

	static vector<vector<Tile>> _tiles;
	vector<Vector2i> _waypoints;

	static vector<Enemy *> _enemies;

	Player * _player;
	SDL_semaphore* _playerSem;

	Camera _cam;
	SDL_Texture* _groundTexture;
	SDL_Texture* _wallTexture;
	SDL_Texture* _enemTexture;
	SDL_Texture* _plTexture;
};
#endif