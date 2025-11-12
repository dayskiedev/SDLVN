#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>

class GameState {
public:
	virtual void EnterState(SDL_Renderer* renderer);
	virtual void ExitState();
	virtual void HandleEvent(SDL_Event& event);
	virtual void Update(double deltaTime);
	virtual void Render();
};

#endif // !GAMESTATE_H
