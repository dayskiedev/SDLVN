#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Config.h"

// this will handle all the saving and loading for the game
// loading a save will tell the intepretor what line to go to
// as well as what sprites / background need to be rendered onto the 
// screen

// right now we don't need to worry about saving and loading

// TODO:
// GET DATA FROM VARIOUS SPOTS, SPRITE LINES BACKGROUND ETC
// save file with proper name
// check for duplicates in save location warn about them
// add save option to game
// add save select option to game (multiple slots)
// add loading
// add load select

// figure out how to save a screenshot of the game with save

#ifndef SAVEMANAGER_H
#define SAVEMANGER_H
#endif 

class SaveManager {
public:
	void Save();
	void Load();
private:
	int saveNum = 0;
	std::ofstream saveFile;
		
	struct spriteSaveFlags {
		std::string spriteObjname;
		std::string curSprite;
		int x, y, w, h;
		double opacity;
	};

	std::string background;
	int scriptLineNumber;
};