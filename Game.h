#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Tile.h"
#include <vector>
#include "FramerateCounter.h"
#include "Camera.h"

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
private:
	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	//SDL_Texture* m_p_Texture;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
	SDL_Surface* m_p_Surface;

	static const int _WORLD_WIDTH = 1000;
	static const int _TILE_SIZE = 64;

	static const float _camSpeed;

	std::vector<std::vector<Tile>> _tiles;
	FramerateCounter _frameCounter;
	Camera _cam;
};
#endif