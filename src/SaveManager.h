
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
#define SAVEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include "Config.h"
#include "SpriteInformation.h"


class SaveManager {
public:
	struct SaveData {
		int scriptLine = _SCRIPT_LINE;
		std::string scriptPath = _SCRIPT_PATH;
		std::string backgroundPath = _BACKGROUND_PATH;
		// sprite name, sprite path, sprite x, sprite y, sprite width, sprite height
		std::vector<SpriteInformation> sprites; // empty by default
		// hashmap containing past choices player has made
		//std::unordered_map<std::string, int> choices;
	};

	void Save();
	bool Load(SaveData& saveData, std::string savePath);

	std::vector<std::string> ScanForSaves();
	bool SaveExists(std::string savePath);

	SaveData& GetSaveData() { return defaultSaveData;  }

private:
	int saveNum = 1;
	std::ofstream File;
	unsigned int size;
	std::string saveFileName = "save3.dat";

	SaveData defaultSaveData;
};

#endif 
