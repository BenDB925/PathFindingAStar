#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include "Tile.h"
#include <vector>
#include "FramerateCounter.h"
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

	static const int _WORLD_WIDTH = 30;
	static const int _TILE_SIZE = 16;
	static int _NUM_ENEMIES;

	static Game * _instance;


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
	vector<vector<Node*>> _navMesh;
	vector<Vector2i> _waypoints;

	vector<Enemy *> _enemies;

	Player * _player;

	FramerateCounter _frameCounter;
	Camera _cam;
	SDL_Texture* _groundTexture;
	SDL_Texture* _wallTexture;
	SDL_Texture* _enemTexture;
};
#endif