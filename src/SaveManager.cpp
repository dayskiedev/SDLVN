#include "SaveManager.h"

// dump game memory into binary and load that?

void SaveManager::Save() {
	std::cout << "Saving test";

	std::string saveLoc = DEFAULT_SAVE_LOCATION + "save0.dat";
	saveFile.open(saveLoc);

	// here we gather data from various sources to add to the file
	saveFile << "lineNumber 0" << std::endl;
	saveFile << "background background.png";
	saveFile << "[SPRITES]" << std::endl;
	saveFile << "rin sprites/rin3.png 12 23 400 400 100" << std::endl;
	saveFile << "choices:" << std::endl;
	saveFile << "bad chill ok";

	saveFile.close();
}