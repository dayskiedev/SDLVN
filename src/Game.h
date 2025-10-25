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

#include "Config.h"

#ifndef GAME_H
#define GAME_H

class Game {
public:
	bool Init();
	void Run(); 
	void Update(SDL_Event e, double deltaTime);
	void Render();
	void Quit();

	bool running = true;
private:
	// Script to load
	std::string script_name = "example_script.vns";

	SDL_Event e;

	// the window we render to
	SDL_Window* gWindow = NULL;

	// window renderer
	SDL_Renderer* gRenderer = NULL;

	// Nabafers
	SpriteManager spriteManager;
	TextManager textManager;
	UIManager uiManager;

	// Main script logic handler
	Interpreter interpreter;

	std::vector<Button*> _buttons;

	Uint64 NOW = 0;
	Uint64 LAST = 0;

	Mix_Music* gPush = NULL;

	// global font
	TTF_Font* gFont = NULL;

	SDL_Color gWhite = { 255,255,255 };
	SDL_Color gBlack = { 0,0,0 };

	// these need to change
	const int tOffsetX = 20;
	const int tOffsetY = 32;

	// will need to remove these at some point.
	Texture gBackground;
	SDL_Rect gBlackBox;
	double deltaTime;

	enum GAME_STATE {
		GAME,
		MENU,
		PAUSE
	};

};

#endif