#include <SDL.h>

#include <iostream>
#include <memory>

#include "Config.h"

#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#include "GameManager.h"
#include "Text.h"

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
	std::unique_ptr<UIManager> menuUi;

	std::unique_ptr<Text> title;
	std::unique_ptr<Text> version;
};

#endif