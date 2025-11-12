#include <SDL.h>

#include <iostream>
#include <memory>

#include "Config.h"
#include "UIManager.h"

#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#include "GameManager.h"

// why does changing this to public work?
class Menu : public GameState {
public:
	void EnterState(SDL_Renderer* renderer, GameManager* gameManager);
	void Update(SDL_Event e, double deltaTime);
	void Render();
	void ExitState();
private:
	// window renderer
	SDL_Renderer* menuRenderer = NULL;
	UIManager menuUi;
};

#endif