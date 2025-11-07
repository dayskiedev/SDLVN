#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include "Config.h"

#include "Game.h"

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager {
public:
	bool Init();
	void Run();
	void Quit();
	
	bool running = true;
	bool pause;

	SDL_Event e;

	// the window we render to
	SDL_Window* gWindow = NULL;

	// window renderer
	SDL_Renderer* gRenderer = NULL;
private:
	Uint64 NOW = 0;
	Uint64 LAST = 0;

	double deltaTime = 0;

	enum GAME_STATE {
		GAME,
		MENU,
		PAUSE
	};

	GAME_STATE gameState = GAME;

	Game _game;

};

#endif