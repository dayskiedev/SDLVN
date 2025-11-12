#include <SDL.h>

#include <iostream>
#include <memory>

#include "Config.h"
#include "UIManager.h"

#ifndef MENU_H
#define MENU_H

#include "GameState.h"

// why does changing this to public work?
class Menu : public GameState {
public:
	void EnterState(SDL_Renderer* renderer);
	void Update(SDL_Event e, double deltaTime);
	void Render();

	void ExitState();
private:
	bool initalised = false;

	// window renderer
	SDL_Renderer* menuRenderer = NULL;
	UIManager menuUi;
};

#endif