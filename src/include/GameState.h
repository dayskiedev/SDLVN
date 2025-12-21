#pragma once

#include <SDL.h>

class GameManager;

class GameState {
public:
	// virtual allows child classes to create their own implementation of the functions
	virtual ~GameState() = default;
	virtual void EnterState(SDL_Renderer* renderer, GameManager* gameManager) = 0;
	virtual void ExitState() = 0;
	virtual void Update(SDL_Event e,double deltaTime) = 0;
	virtual void Render() = 0;
protected:
	GameManager* _gameManager;
};
