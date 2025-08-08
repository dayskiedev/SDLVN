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

// TODO: 
// CLEAN UP CODE
// do wee need pointers for everything?

const int S_MID_X = SCREEN_WIDTH / 2 - 200;
const int S_MID_Y = SCREEN_HEIGHT / 2 - 250;

const int tOffsetX = 20;
const int tOffsetY = 32;

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
UIManager uiManager;
Interpreter interpreter;

std::vector<Button*> _buttons;

Texture gBackground;
SDL_Rect gBlackBox;


bool init() {
	bool success = true;

	//initialze sdl
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL could not be initialized!" << std::endl;
		success = false;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow("SDLVN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void Update(SDL_Event e) {

	// main game logic, handle input

	// here we execute the current line in the interpreter before checking for any input
	interpreter.Run(e, spriteManager, textManager, uiManager, gBackground);

	for (Button* b : uiManager.GetUiVector()) {
		b->Update(e);
	}
}

void renderGame() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	// layer -1 background
	gBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// layer 1 character sprites
	for (Sprite* s : spriteManager.getSpriteVector()) {
		s->render(s->getX(), s->getY(), s->getWidth() / 1.5, s->getHeight() / 1.5);
	}
	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);
	SDL_RenderFillRect(gRenderer, &gBlackBox);

	// layer 2 text
	int index = 0;
	for (Texture* t : textManager.getTextVector()) {
		t->render(tOffsetX,(tOffsetY * index) + tOffsetX);
		index++;
	}

	// layer 3 buttons/ui?
	for (Button* b : uiManager.GetUiVector()) {
		b->render(b->getX(), b->getY());
		b->showText();
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
	spriteManager.setSpriteTexPath(GLOBAL_SPRITES_PATH);

	textManager.setRenderer(gRenderer);
	textManager.setFont(GLOBAL_FONT_PATH);

	uiManager.setRenderer(gRenderer);

	//interfaceManager()?

	gBackground.setRenderer(gRenderer);

	/// REMOVE LATER
	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//gPush = Mix_LoadMUS("music/push.mp3");
	//if (gPush == NULL) {
	//	std::cout << "Unable to push push " << Mix_GetError() << std::endl;
	//}

	if (!interpreter.OpenScript(GLOBAL_SCRIPTS_PATH + "example_script.vns")) { return -1; }

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
