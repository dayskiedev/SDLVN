#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "SpriteManager.h"
#include "TextManager.h"
#include "Interpreter.h"
#include "Button.h"
#include "Config.h"

#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "GameManager.h"

// we dony want scenes to interact with the managaer, but we need them to change scenes

class Game : public GameState {
public:
	void EnterState(SDL_Renderer* renderer, GameManager* gameManager);
	void Update(SDL_Event e, double deltaTime);
	void Render();
	void ExitState();
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
	const int tOffsetY = 32;

	// game specific UI
	std::shared_ptr<Sprite> gBackground = std::make_shared<Sprite>();
	SDL_Rect gBlackBox;

	Interpreter interpreter;
};

#endif