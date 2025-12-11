#pragma once

#include <SDL.h>

#include <iostream>
#include <memory>

#include "Config.h"
#include "OptionsUI.h"
#include "SaveLoadUI.h"
// inheretence requires the full definition of a base class, so we leave the include in the header
#include "GameState.h" 

class GameManager;
class UIManager;

class Text;

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

	enum MENU_STATE {
		MAIN_MENU,
		LOAD_SAVE,
		OPTIONS
	};

	MENU_STATE menuState = MAIN_MENU;
	std::unique_ptr<OptionsUI> optionsUI = std::make_unique<OptionsUI>();
	std::unique_ptr<SaveLoadUI> saveLoadUI = std::make_unique<SaveLoadUI>();
};