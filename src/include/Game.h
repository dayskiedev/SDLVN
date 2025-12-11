#pragma once

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "Config.h"
#include "Interpreter.h"
#include "GameState.h"
#include "SaveLoadUI.h"
#include "OptionsUI.h"

class GameManager;
class UIManager;

// we dony want scenes to interact with the managaer, but we need them to change scenes

class Game : public GameState {
public:
	void EnterState(SDL_Renderer* renderer, GameManager* gameManager);
	void Update(SDL_Event e, double deltaTime);
	void Render();
	void ExitState();

	void CallSaveFunc();
private:
	// Script to load
	std::string script_name = "example_script.vns";

	// window renderer
	SDL_Renderer* gameRenderer = NULL;

	// we have these as shared pointers because they are accessed by both
	// Game.cpp and INterpreter.cpp, so only get deleted if they go out of scope in both file 
	// (ie changing back to main menu)
	std::shared_ptr<SpriteManager> spriteManager = std::make_shared <SpriteManager>();;
	std::shared_ptr<TextManager> textManager = std::make_shared<TextManager>();
	std::shared_ptr<UIManager> uiManager = std::make_shared<UIManager>();

	// Main script logic handler
	// need to initialise referneces in constructor

	SDL_Color gWhite = { 255,255,255 };
	SDL_Color gBlack = { 0,0,0 };

	// these need to change
	const int tOffsetX = 20;
	const int tOffsetY = 34;

	
	enum GAME_STATE {
		RUNNING,    // main game loop running
		PAUSED,		// when the game is paused, switch to sub states
		NO_TEXT,	// when we want to see sprites and backgrounds without text
	};

	GAME_STATE currentState = RUNNING;

	enum PAUSE_STATE {
		PAUSED_MENU,
		SAVE_MENU,
		LOAD_MENU,
		OPTIONS_MENU			
	};

	PAUSE_STATE pauseState = PAUSED_MENU;
	bool swappingScenes = false;

	std::shared_ptr<Sprite> gBackground = std::make_shared<Sprite>();
	SDL_Rect gBlackBox;

	std::shared_ptr<Interpreter> interpreter = std::make_shared<Interpreter>();

	// PAUSE UI STUFF
	std::vector<std::shared_ptr<Texture>> PauseMainMenuUI;
	std::shared_ptr<Sprite> uma = std::make_shared<Sprite>();

	std::unique_ptr<OptionsUI> optionsUI = std::make_unique<OptionsUI>();
	std::unique_ptr<SaveLoadUI> saveLoadUI = std::make_unique<SaveLoadUI>();
};
