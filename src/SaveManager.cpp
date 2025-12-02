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

void SaveManager::Save(SaveData saveRawInfo) {

	// need to be able to select a save file slot
	std::cout << "Saving file to " << DEFAULT_SAVE_LOCATION + saveFileName << std::endl;

	std::ofstream outfile(DEFAULT_SAVE_LOCATION + saveFileName, std::ofstream::binary);

	//std::string text = ("testingsave");
	//size = text.size();

	//outfile.write(reinterpret_cast<char *>(&size), sizeof(size));
	//outfile.write(text.c_str(), text.size());
	// we need to tell the binary file what we are writing to it, and how big it is (the point of sizeof)
	
	std::string scriptLoc		= saveRawInfo.scriptPath;
	int scriptLine				= saveRawInfo.scriptLine;
	std::string backgroundLoc	= saveRawInfo.backgroundPath;
	int numCharacters			= saveRawInfo.sprites.size();

	std::cout << "Saving raw data:" << std::endl;
	std::cout << "Script location: " << scriptLoc << std::endl;
	std::cout << "Script line: " << scriptLine << std::endl;
	std::cout << "Background location: " << backgroundLoc << std::endl;
	std::cout << "Number of characters: " << numCharacters << std::endl;

	unsigned int size;

	outfile.write(reinterpret_cast<const char*>(&SAVE_VERSION), sizeof(SAVE_VERSION));	// SAVE VERSION

	size = scriptLoc.size(); // string does not store its size in binary so we write it
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// script save loc
	outfile.write(scriptLoc.c_str(), scriptLoc.size());

	outfile.write(reinterpret_cast<char*>(&scriptLine), sizeof(scriptLine));			// SCRIPT LINE NUMBER	

	size = backgroundLoc.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// background directory location
	outfile.write(backgroundLoc.c_str(), backgroundLoc.size());

	outfile.write(reinterpret_cast<char*>(&numCharacters), sizeof(numCharacters));		// number of characters to save/load

	for (auto s : saveRawInfo.sprites) {												// character specific info
		// sprite name
		size = s.spriteName.size();
		outfile.write(reinterpret_cast<char*>(&size), sizeof(size));
		outfile.write(s.spriteName.c_str(), s.spriteName.size());

		//// sprite texture path
		size = s.spriteLocation.size();
		outfile.write(reinterpret_cast<char*>(&size), sizeof(size));
		outfile.write(s.spriteLocation.c_str(), s.spriteLocation.size());

		//// sprite width, height, x, y
		outfile.write(reinterpret_cast<char*>(&s.w), sizeof(s.w));
		outfile.write(reinterpret_cast<char*>(&s.h), sizeof(s.h));
		outfile.write(reinterpret_cast<char*>(&s.x), sizeof(s.x));
		outfile.write(reinterpret_cast<char*>(&s.y), sizeof(s.y));

	}

	outfile.close();
}

bool SaveManager::Load(SaveData& saveData, std::string savePath) {
	std::cout << "Loading " << savePath << std::endl;
	std::ifstream infile(savePath, std::ifstream::binary);
	if (!infile.is_open()) {
		std::cout << "Failed to open file!" << std::endl;
		return false;
	}

	// this will be filled with loaded data from save file;

	unsigned size = 0;

	// READING IN GAME DATA
	int rSaveVer = 0;
	std::string rScriptLoc = "";
	int rScriptLine = 0;
	std::string rBacLoc = "";
	int rNumChar = 0;
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
		return false;
	}

	infile.read(reinterpret_cast<char*>(&size), sizeof(size));		
	rScriptLoc.resize(size);
	infile.read(&rScriptLoc[0], rScriptLoc.size());								// read in script location

	infile.read(reinterpret_cast<char*>(&rScriptLine), sizeof(rScriptLine));	// read in script line number

	infile.read(reinterpret_cast<char*>(&rScriptLine), sizeof(rScriptLine));	// read in number of characters

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

	saveData.scriptLine = 2;
	return true;
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