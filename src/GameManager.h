#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Config.h"

#include "GameState.h"

// states
#include "Menu.h"
#include "Game.h"

class GameManager {
public:
	bool Init();
	void Run();
	void Quit();

	void ChangeState(GameState* state);
	
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

	GameState* currentState;

	Game _game;
	Menu _menu;

};

#endif