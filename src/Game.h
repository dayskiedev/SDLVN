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

class Game {
public:
	bool Init(SDL_Renderer* renderer);
	void Run(SDL_Event e, double deltaTime);
	void Update(SDL_Event e, double deltaTime);
	void Render();
private:
	bool initalised = false;
	// Script to load
	std::string script_name = "example_script.vns";

	// window renderer
	SDL_Renderer* gameRenderer = NULL;

	// Nabafers
	SpriteManager spriteManager;
	TextManager textManager;
	UIManager uiManager;

	// Main script logic handler
	Interpreter interpreter;

	std::vector<Button*> _buttons;

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
};

#endif