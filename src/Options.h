#include <SDL.h>

#include <iostream>
#include <memory>

#include "Config.h"
#include "UIManager.h"

#ifndef OPTIONS_H
#define OPTIONS_H

#include "GameState.h"
#include "GameManager.h"

class Options : public GameState {
	void EnterState(SDL_Renderer* renderer, GameManager* gameManager);
	void Update(SDL_Event e, double deltaTime);
	void Render();
	void ExitState();
private:
	// window renderer
	SDL_Renderer* optionRenderer = NULL;
	UIManager optionUi;
};

#endif // !
