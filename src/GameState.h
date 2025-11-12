#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>

class GameState {
public:
	virtual void EnterState(SDL_Renderer* renderer) = 0;
	virtual void ExitState() = 0;
	virtual void Update(SDL_Event e,double deltaTime) = 0;
	virtual void Render() = 0;
};

#endif // !GAMESTATE_H
