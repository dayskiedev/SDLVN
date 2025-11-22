#include "SaveManager.h"

// dump game memory into binary and load that?

// SAVE STRUCTURE:
// SAVE VERSION
// SCRIPT LOCATION
// TIME
// DATE (DAY/MNTH)
// SCRIPT LINE (THEN WE WILL AUTO READ THE LINE)
// BACKGROUND TO LOAD
// [CHARACTERS]
// number of characters
// sprite name
// sprite file location
// x
// y
// w
// h
// [CHOICES]
// SET EVERY SAVED CHOICE

void SaveManager::Save() {
	std::cout << "Saving file to " << DEFAULT_SAVE_LOCATION + saveFileName << std::endl;

	std::ofstream outfile(DEFAULT_SAVE_LOCATION + saveFileName, std::ofstream::binary);

	//std::string text = ("testingsave");
	//size = text.size();

	//outfile.write(reinterpret_cast<char *>(&size), sizeof(size));
	//outfile.write(text.c_str(), text.size());
	// we need to tell the binary file what we are writing to it, and how big it is (the point of sizeof)
	
	std::string scriptLoc = "script/location/path";
	int scriptLine = 12;
	std::string backgroundLoc = "background/directory.png";

	// will be a loop
	std::string characterName = "lucio";
	std::string characterSprite = "sprites/lucio_mad.png";

	// also a loop
	std::string choiceName = "kill your dad?";
	int choiceValue = 1; // flipped

	unsigned int size;

	outfile.write(reinterpret_cast<const char*>(&SAVE_VERSION), sizeof(SAVE_VERSION));	// SAVE VERSION

	size = scriptLoc.size(); // string does not store its size in binary so we write it
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// script save loc
	outfile.write(scriptLoc.c_str(), scriptLoc.size());

	outfile.write(reinterpret_cast<char*>(&scriptLine), sizeof(scriptLine));			// SCRIPT LINE NUMBER	

	size = backgroundLoc.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// background directory location
	outfile.write(backgroundLoc.c_str(), backgroundLoc.size());

	// CHARACTER DATA
	size = characterName.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// CHARACTER NAME
	outfile.write(characterName.c_str(), characterName.size());

	size = characterSprite.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// CHARACTER SPRITE DIRECTORY LOCATION
	outfile.write(characterSprite.c_str(), characterSprite.size());

	// CHOICE DATA
	size = choiceName.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// CHOICE NAME
	outfile.write(choiceName.c_str(), choiceName.size());

	outfile.write(reinterpret_cast<char*>(&choiceValue), sizeof(choiceValue));			// SCRIPT LINE NUMBER

	outfile.close();
}

void SaveManager::Load() {
	std::cout << "Loading " << DEFAULT_SAVE_LOCATION << saveFileName << std::endl;
	std::ifstream infile(DEFAULT_SAVE_LOCATION + saveFileName, std::ifstream::binary);
	if (!infile.is_open()) {
		std::cout << "Failed to open file!" << std::endl;
		return;
	}

	unsigned size = 0;

	// READING IN GAME DATA
	int rSaveVer = 0;
	std::string rScriptLoc = "";
	int rScriptLine = 0;
	std::string rBacLoc = "";
	// number of characters
	std::string rCharName = "";
	std::string rCharSpriLoc = "";
	// character sprite position
	// number of choices
	std::string rChoiceName = "";
	int rChoiceValue = 99;

	infile.read(reinterpret_cast<char*>(&rSaveVer), sizeof(rSaveVer));

	// safety check for saves, because we may change the save layout we want to change this (should be removed in final ver)
	if (rSaveVer != SAVE_VERSION) {
		std::cout << "Error: mismatched save version, read: " << rSaveVer << " when current version is: " << SAVE_VERSION << std::endl;
		return;
	}

	infile.read(reinterpret_cast<char*>(&size), sizeof(size));
	rScriptLoc.resize(size);
	infile.read(&rScriptLoc[0], rScriptLoc.size());

	infile.read(reinterpret_cast<char*>(&rScriptLine), sizeof(rScriptLine));

	infile.read(reinterpret_cast<char*>(&size), sizeof(size));
	rBacLoc.resize(size);
	infile.read(&rBacLoc[0], rBacLoc.size());

	infile.read(reinterpret_cast<char*>(&size), sizeof(size));
	rCharName.resize(size);
	infile.read(&rCharName[0], rCharName.size());

	infile.read(reinterpret_cast<char*>(&size), sizeof(size));
	rCharSpriLoc.resize(size);
	infile.read(&rCharSpriLoc[0], rCharSpriLoc.size());

	infile.read(reinterpret_cast<char*>(&size), sizeof(size));
	rChoiceName.resize(size);
	infile.read(&rChoiceName[0], rChoiceName.size());

	infile.read(reinterpret_cast<char*>(&rChoiceValue), sizeof(rChoiceValue));

	infile.close();

	std::cout << std::endl;
	std::cout << "######### SAVE INFORMATION #########" << std::endl;
	std::cout << "Save version: " << rSaveVer << " Current Save Version: " << rSaveVer << std::endl;
	std::cout << "Script path: " << rScriptLoc << std::endl;
	std::cout << "Script line number: " << rScriptLine << std::endl;
	std::cout << "Background path: " << rBacLoc << std::endl;
	std::cout << "######### CHARACTERS #########" << std::endl;
	std::cout << "Character name: " << rCharName << std::endl;
	std::cout << "Character sprite path: " << rCharSpriLoc << std::endl;
	std::cout << "######### CHOICES #########" << std::endl;
	std::cout << "Choice name: " << rChoiceName << std::endl;
	std::cout << "Choice value: " << rChoiceValue << std::endl;

}

std::vector<std::string> SaveManager::ScanForSaves() {
	std::string path = DEFAULT_SAVE_LOCATION;
	std::vector<std::string> saveFiles;

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.path().extension() == ".dat") {
			saveFiles.push_back(entry.path().string());
		}
	}

	return saveFiles;
}

bool SaveManager::SaveExists(std::string savePath) {
	return std::filesystem::exists(savePath);
}