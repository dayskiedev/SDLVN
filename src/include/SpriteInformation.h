#pragma once

#include <iostream>

// only really used to easily extract and parse sprite info from whatever
// sprites are being rendered into the save data struct for saving

struct SpriteInformation {
	std::string spriteName;
	std::string spriteLocation;
	double spriteScale;
	int x;
	int y;
	int w;
	int h;
};