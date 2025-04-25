#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

// this gives an erro im assuming because sprite defines texture or something?
//#include "Texture.h"
#include "SpriteManager.h"
// sprite manager (includes) sprite (includes) texture
// daisy chaining is a little weird
		
/// <summary>
/// MY CUSTOM VN ENGINE
/// GOALS:
/// - bE ABLE TO PLAY MY OWN VISUAL NOVEL
/// - CUSTOM SCRIPTING LANGUAGE TO CREATE THIS NOVEL
/// example script:
/// 
 //*scene rain_01_02
 //*music sad	.mp3
 //sakura: Its really quiet out here
 //*sprite sakura sakura_front_face.png
 //*music stop
 //sakura: You'll walk home with me, right?
 //*choice a b
 //a: Of course
 //b: fuckoff
/// 
/// TODO (ALOT
///	SPRITE CLASS TO STORE INFO ABOUT SPRITE
/// A universal sprite box so i dont have to manuelly set the scale every time???
/// The png's should stretch to fit the box, not the other way around....
/// SOUND
///  - Basic ass music idea
///  - make it myself?? xd
/// MENU

/// FIRST MILESTONE
/// - Have a sprite appear on screen, with a text box, say some stuff, change sprites and end
/// - DONE
/// 
/// SECOND MILESTONE
/// - Have two characters appear on screen and talk - DONE
/// - Have a choice that changes the dialouge
/// </summary>

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
SpriteManager spriteManager(gSpritesPath);

// this will become text read from a file, so array size will not matter, it will
// be fed to the vector as a string

// enter = add a new character to the scree

// fix iteration over the script so i dont have these goofy empty text spaces
// 	"*enter rin rin.png CENTRE",
//"*exit saber",
// doing these two back to back causes a vector subscript out range
// something to do with the text vector when text is empty?

// TODO:
// fix sprite positioning, different sprites go off center
// (i swear im positioning based on sprtie width, so the origin should not change?)
// really need to fix how the game moves forward
// this will solve text 


//
// Tenporary globals to be replaced
//

std::string exampleCommandLine[50] = { 
	"*enter saber saber.png CENTRE",
	"*text So, what am I doing here exactly?",
	"*text Hurry up and say something!",
	"*setsprite saber saber4.png",
	"*text @",
	"*enter rin rin.png CENTRE",
	"*exit saber",
	"*text hiiiii saber",
	"*text ok rude",
	"*setsprite rin rin2.png",
	"*text She didn't even say hi back...",
	"*setsprite rin rin3.png",
	"*text Did I do something to make her mad?",
	"*text @",
	"exit rin"
};
	
Texture gBackground;
SDL_Rect gBlackBox;
std::vector<Texture*> TextVec;

///
/// End temp globals
///

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

std::vector<std::string> splitString(std::string s) {
	std::stringstream ss(s);
	std::string word;
	std::vector<std::string> words;

	while (ss >> word) {
		words.push_back(word);
	}
	return words;
}

// some sort of interpreter class to read the file

void addText(SDL_Event e) {
	// maybe add a wait for input? next time idk
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_SPACE:
			Texture* text = new Texture;
			text->setRenderer(gRenderer);
			text->setFont(gFont);

			std::string rmpText = exampleCommandLine[cCount].erase(0,6);
			text->loadFromRenderedText(rmpText, gWhite);
			TextVec.push_back(text);
			cCount++;
		}
	}
}
void clearText(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_SPACE:
			for (Texture* t : TextVec) {
				delete t;
			}
			TextVec.clear();
			cCount++;
		}
	}
}

void setBackground(std::string filename) {
	gBackground.loadFromFile(backgroundsPath + filename);
}

void updateGame(SDL_Event e) {
	// this should just contain the background
	char commandCheck = exampleCommandLine[cCount][0];

	if (commandCheck == '*') {
		std::vector<std::string> commandArgs = splitString(exampleCommandLine[cCount]);

		if (commandArgs[0] == "*enter") {
			spriteManager.addSprite(commandArgs[1], commandArgs[2], "CENTRE");
			cCount++;
		}

		if (commandArgs[0] == "*exit") {
			spriteManager.removeSprite(commandArgs[1]);
			cCount++;
		}

		//FIX THIS SHIT DO NOT LEAVE LIKE THIS
		if (commandArgs[0] == "*setsprite") {
			spriteManager.setSprite(commandArgs[1], commandArgs[2]);
			cCount++;
		}
		
		if (commandArgs[0] == "*text") {
			if (commandArgs[1] == "@") {
				clearText(e);
			}
			else {
				addText(e);
			}
		}

		if (commandArgs[0] == "*setbackground") {
			setBackground(commandArgs[1]);
			cCount++;
		}
	}
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
	for (Texture* t : TextVec) {
		t->render(tOffsetX,(tOffsetY * index) + tOffsetX);
		index++;
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

	gBackground.setRenderer(gRenderer);
	gBackground.loadFromFile(backgroundsPath + "entrance.png");

	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT }; 
	std::string gFontpath = gFontsPath + "sazanami-gothic.ttf";
	gFont = TTF_OpenFont(gFontpath.c_str(), 28);

	while (!quit) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			quit = true;
		}

		updateGame(e);
		SDL_RenderClear(gRenderer);
		renderGame();
		SDL_RenderPresent(gRenderer);
	}

	close();

	return 0;
}
