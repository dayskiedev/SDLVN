#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "SpriteManager.h"
#include "TextManager.h"

#include "Interpreter.h"

// make variable
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// should change these to be only division, pixel count will change dpending on the screen
const int S_MID_X = SCREEN_WIDTH / 2 - 200;
const int S_MID_Y = SCREEN_HEIGHT / 2 - 250;

const int tOffsetX = 20;
const int tOffsetY = 32;

const std::string gSpritesPath = "sprites/";
const std::string backgroundsPath = "backgrounds/";
const std::string gFontsPath = "fonts/";

int cCount = 0;

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
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "SDL_Image could not be initialised! " << IMG_GetError() << std::endl;
					success = false;
				}

				if (TTF_Init() == -1) {
					std::cout << "SDL_TTF could not be initialised! " << TTF_GetError() << std::endl;
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

void updateGame(SDL_Event e) {
	interpreter.Run(e, spriteManager, textManager);
	// allows room for other stuff, like menu checking? if we want to pause?
}

void renderGame() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	gBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	for (Sprite* s : spriteManager.getSpriteVector()) {
		s->render(s->getX(), s->getY(), s->getWidth() / 1.6, s->getHeight() / 1.6);
	}
	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);
	SDL_RenderFillRect(gRenderer, &gBlackBox);

	int index = 0;
	for (Texture* t : textManager.getTextVector()) {
		t->render(tOffsetX,(tOffsetY * index) + tOffsetX);
		index++;
	}

	int b_x_mid = (SCREEN_WIDTH / 2) - (button.w / 2);
	int b_y_mid = (SCREEN_HEIGHT / 2) - (button.h / 2);
	int x, y;

	SDL_GetMouseState(&x, &y);

	// custom overlap?

	//std::cout << "start " << button.y << " end " << button.y+button.h << "\n";

	// scuffed overlap checking
	bool olap = false;
	if (x >= button.x && x <= button.x + button.w) {
		if (y >= button.y && y <= button.y + button.h) {
			olap = true;
		}
	}

	if (olap) {
		std::cout << "Overlaping\n";
		olap = false;
	}
	else {
		std::cout << "not overlapping\n";
	}

	//std::cout << "Mouse X: " << x << " Mouse Y: " << y << "\n";
	b_size = 100;
	button.x = b_x_mid;
	button.y = b_y_mid;
	button.w = b_size;
	button.h = b_size;
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 100);
	SDL_RenderFillRect(gRenderer, &button);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);

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

	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT }; 
	

	if (!interpreter.OpenScript("scripts/example_script.vns")) {
		std::cout << "Failed to load script!" << std::endl;
		return -1;
	}

	while (!quit) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			quit = true;
		}

		updateGame(e);
		renderGame();
		SDL_RenderPresent(gRenderer);
	}

	close();

	return 0;
}
