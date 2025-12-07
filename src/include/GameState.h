#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>

class GameManager;

class GameState {
public:
	virtual ~GameState() = default;
	virtual void EnterState(SDL_Renderer* renderer, GameManager* gameManager) = 0;
	virtual void ExitState() = 0;
	virtual void Update(SDL_Event e,double deltaTime) = 0;
	virtual void Render() = 0;
protected:
	GameManager* _gameManager;
};

#endif // !GAMESTATE_H
