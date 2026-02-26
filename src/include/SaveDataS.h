#pragma once

#include <iostream>
#include <vector>

#include "Config.h"
#include "SpriteInformation.h"

// here we have info that will be passed through the game into the save manager and accessed again to load data
// i split it into its own header so the interpreter can use the format without needing to directly touch the savemanaher
// only the game manager should touch that.

struct SaveData {
	int scriptLine = _SCRIPT_LINE;
	std::string scriptPath = _SCRIPT_PATH;
	std::string backgroundPath = _BACKGROUND_PATH;
	// sprite name, sprite path, sprite x, sprite y, sprite width, sprite height
	std::vector<SpriteInformation> sprites; // empty by default
	// hashmap containing past choices player has made
	//std::unordered_map<std::string, int> choices;

	std::string musicPath = "";
	bool musPlaying = false;
};