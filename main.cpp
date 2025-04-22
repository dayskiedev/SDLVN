#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

// this gives an erro im assuming because sprite defines texture or something?
//#include "Texture.h"
#include "Sprite.h"
		
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
/// - They have fade in and out animations, and fade transition sprites
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

// this will become text read from a file, so array size will not matter, it will
// be fed to the vector as a string

// enter = add a new character to the scree

// fix iteration over the script so i dont have these goofy empty text spaces
// 	"*enter rin rin.png CENTRE",
//"*exit saber",
// doing these two back to back causes a vector subscript out range
// something to do with the text vector when text is empty?

// TODO:
// MOVE SPRITE MANAGEMENT TO ITS OWN FILE
// really need to fix how the game moves forward
// this will solve text 

std::string exampleCommandLine[50] = { 
	"*enter saber saber.png CENTRE",
	"*text So, what am I doing here exactly?",
	"*text Hurry up and say something!",
	"*setsprite saber saber4.png",
	"*text @",
	"*enter rin rin.png CENTRE",
	"*exit saber",
	"*text hiiiii saber",
	"*text ok bye",
	"*exit rin",
	"*text @"
};
	

Texture gBackground;
SDL_Rect gBlackBox;
std::vector<Texture*> TextVec;
std::vector<Sprite*> SpriteVec;

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

std::vector<Sprite*>::iterator findSpriteByName(std::string spriteName) {
	auto vecSpriteElement = std::find_if(SpriteVec.begin(), SpriteVec.end(),
		[spriteName](Sprite* s) {
			return s->GetSpriteName() == spriteName;
		});

	if (vecSpriteElement != SpriteVec.end()) {
		// not sure why it needed the brackets
		return vecSpriteElement;
	}
	else {
		std::cout << "Unable to find sprite obj. " << spriteName << " not found!" << std::endl;;
		return SpriteVec.end();
	}
}

void setSprite(std::string spriteObjName, std::string spriteName) {
	// check if spritepath is valid
	// check if sprite name matches any in spritelist
		
	// wtd is this vro
	auto spriteToChange = findSpriteByName(spriteObjName);
	if (spriteToChange == SpriteVec.end()) {
		std::cout << "Unable to change sprite object, " << spriteObjName << " not found!" << std::endl;
		return;
	}
	(*spriteToChange)->loadFromFile(gSpritesPath + spriteName);
}
void addSprite(std::string spriteName, std::string spriteTexName, std::string pos) {

	// pos will point to a dict with key pair values for x and y
	// int x = get x value from pos
	// int y = get y value from pos

	Sprite* sprite = new Sprite;
	
	// this could all be in a constructor?
	sprite->setRenderer(gRenderer);

	sprite->SetSpriteName(spriteName);
	std::string spritePath = gSpritesPath + spriteTexName;
	sprite->loadFromFile(spritePath);
	sprite->setX(S_MID_X);
	sprite->setY(S_MID_Y);

	SpriteVec.push_back(sprite);
}
void removeSprite(std::string spriteObjName) {
	// chanfe to using a sprite name
	auto spriteToErase = findSpriteByName(spriteObjName);
	if (spriteToErase == SpriteVec.end()) { 
		std::cout << "Unable to remove sprite object, " << spriteObjName << " not found!" << std::endl;
		return; 
	}

	delete *spriteToErase;
	SpriteVec.erase(spriteToErase);
}

void updateGame(SDL_Event e) {
	// this should just contain the background
	char commandCheck = exampleCommandLine[cCount][0];

	if (commandCheck == '*') {
		std::vector<std::string> commandArgs = splitString(exampleCommandLine[cCount]);

		if (commandArgs[0] == "*enter") {
			addSprite(commandArgs[1], commandArgs[2], "CENTRE");
			cCount++;
		}

		if (commandArgs[0] == "*exit") {
			removeSprite(commandArgs[1]);
			cCount++;
		}

		//FIX THIS SHIT DO NOT LEAVE LIKE THIS
		if (commandArgs[0] == "*setsprite") {
			setSprite(commandArgs[1], commandArgs[2]);
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

	for (Sprite* s : SpriteVec) {
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

	// LOAD GLOBALS

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
