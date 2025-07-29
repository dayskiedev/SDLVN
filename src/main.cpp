#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "Config.h"

#include "SpriteManager.h"
#include "TextManager.h"

#include "Interpreter.h"

#include "Button.h"

// make variable
// should change these to be only division, pixel count will change dpending on the screen


const int S_MID_X = SCREEN_WIDTH / 2 - 200;
const int S_MID_Y = SCREEN_HEIGHT / 2 - 250;

const int tOffsetX = 20;
const int tOffsetY = 32;

const std::string gSpritesPath = "sprites/";
const std::string backgroundsPath = "backgrounds/";
const std::string gFontsPath = "fonts/";

// enum for positons

int cCount = 0;

Mix_Music* gPush = NULL;

// global font
TTF_Font* gFont = NULL;
SDL_Color gWhite = { 255,255,255 };
SDL_Color gBlack = { 0,0,0 };

// the window we render to
SDL_Window* gWindow = NULL;

// window renderer
SDL_Renderer* gRenderer = NULL;

// manging of game sprites
SpriteManager spriteManager;
TextManager textManager;
Interpreter interpreter;

std::vector<Button*> _buttons;

Texture gBackground;
SDL_Rect gBlackBox;

int b_size = 50;
SDL_Rect button = { 0, 0,0, 0 };


// to do: selection:
// step 1: render rectangle 
// step 2: add text inside it
// step 3: size rectangle to text
// step 4: make rectangle clickable
// step 5: do something after clicking said textbox

bool init() {
	bool success = true;

	//initialze sdl
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL could not be initialized!" << std::endl;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			std::cout << "Window could not be created!" << std::endl;
			success = false;
		}
		else {
			// Create Renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 255, 175, 222, 0xFF);
				SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

				// imgs
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "SDL_Image could not be initialised! " << IMG_GetError() << std::endl;
					success = false;
				}

				// fonts
				if (TTF_Init() == -1) {
					std::cout << "SDL_TTF could not be initialised! " << TTF_GetError() << std::endl;
					success = false;
				}

				// audio
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					std::cout << "SDL_mixer could not be initalised! " << Mix_GetError() << std::endl;
					success = false;
				}

			}
		}
	}

	return success;
}

void close() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

void setBackground(std::string filename) {
	gBackground.loadFromFile(backgroundsPath + filename);
}

void Update(SDL_Event e) {

	// main game logic, handle input

	// here we execute the current line in the interpreter before checking for any input
	interpreter.Run(e, spriteManager, textManager);

	// we want to do ui input as well


	// loop through each button

	for (Button* b : _buttons) {
		if (b->OverlappingCheck() && e.type == SDL_MOUSEBUTTONDOWN) {
			b->OnClick();
		}
	}
}

void renderGame() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	gBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// eventually have some sort of master z layer for every sprite?
	for (Sprite* s : spriteManager.getSpriteVector()) {
		s->render(s->getX(), s->getY(), s->getWidth() / 1.5, s->getHeight() / 1.5);
	}
	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);
	SDL_RenderFillRect(gRenderer, &gBlackBox);

	int index = 0;
	for (Texture* t : textManager.getTextVector()) {
		t->render(tOffsetX,(tOffsetY * index) + tOffsetX);
		index++;
	}

	// ui

	for (Button* b : _buttons) {
		b->render(b->getX(), b->getY());
	}
}

int main(int argc, char* args[]) {
	SDL_Event e;
	bool quit = false;

	if (!init()) {
		std::cout << "Failed to Init!" << std::endl;
		return -1;
	}

	// LOAD GLOBALS (there has to be a better way to do this?
	spriteManager.setRenderer(gRenderer);
	spriteManager.setSpriteTexPath(gSpritesPath);

	textManager.setRender(gRenderer);
	textManager.setFont(gFontsPath + "sazanami-gothic.ttf");

	//interfaceManager()?

	gBackground.setRenderer(gRenderer);
	gBackground.loadFromFile(backgroundsPath + "entrance.png");


	/// REMOVE LATER
	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	Button* test_button = new Button;
	test_button->setRenderer(gRenderer);
	test_button->loadFromFile(gSpritesPath + "anon.png");
	test_button->setWidth(250);
	test_button->setHeight(250);
	test_button->setX(100);
	test_button->setY(100);

	_buttons.push_back(test_button);

	gPush = Mix_LoadMUS("music/push.mp3");
	if (gPush == NULL) {
		std::cout << "Unable to push push " << Mix_GetError() << std::endl;
	}

	if (!interpreter.OpenScript("scripts/example_script.vns")) {
		std::cout << "Failed to load script!" << std::endl;
		return -1;
	}

	while (!quit) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			quit = true;
		}

		Update(e);
		renderGame();
		SDL_RenderPresent(gRenderer);
	}

	close();

	return 0;
}
