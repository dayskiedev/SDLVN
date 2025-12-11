#pragma once

#include <SDL.h>

#include <iostream>
#include <memory>
#include <string>

#include "Config.h"
#include "UIManager.h"

#include "GameState.h"
#include "GameManager.h"
#include "SaveManager.h"

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

