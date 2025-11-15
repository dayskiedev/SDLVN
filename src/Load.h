#include <SDL.h>

#include <iostream>
#include <memory>

#include "Config.h"
#include "UIManager.h"

#ifndef LOAD_H
#define LOAD_H

#include "GameState.h"
#include "GameManager.h"

class Load : public GameState {
	void EnterState(SDL_Renderer* renderer, GameManager* gameManager);
	void Update(SDL_Event e, double deltaTime);
	void Render();
	void ExitState();
private:
	// window renderer
	SDL_Renderer* loadRenderer = NULL;
	std::unique_ptr<UIManager> loadUI;
};

#endif // !

