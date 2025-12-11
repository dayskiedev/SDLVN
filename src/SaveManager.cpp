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

void SaveManager::Save(SaveData saveRawInfo, std::string savePath) {

	// need to be able to select a save file slot
	std::cout << "Saving file to " << savePath << std::endl;

	std::ofstream outfile(savePath, std::ofstream::binary);

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
	std::string rSprName = "";
	std::string rSpriteLoc = "";
	int w, h, x, y;
	SpriteInformation rTempSpriteInfo;
	std::vector<SpriteInformation> rTempSpriteInfoVec;
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

	infile.read(reinterpret_cast<char*>(&size), sizeof(size));					// read in background loc
	rBacLoc.resize(size);
	infile.read(&rBacLoc[0], rBacLoc.size());

	infile.read(reinterpret_cast<char*>(&rNumChar), sizeof(rNumChar));			// read in number of characters

	// loading character info
	for (int i = 0; i < rNumChar; ++i) {
		// sprite name 
		infile.read(reinterpret_cast<char*>(&size), sizeof(size));
		rSprName.resize(size);
		infile.read(&rSprName[0], rSprName.size());

		// sprite location
		infile.read(reinterpret_cast<char*>(&size), sizeof(size));
		rSpriteLoc.resize(size);
		infile.read(&rSpriteLoc[0], rSpriteLoc.size());

		// w h x y
		infile.read(reinterpret_cast<char*>(&w), sizeof(w));
		infile.read(reinterpret_cast<char*>(&h), sizeof(h));
		infile.read(reinterpret_cast<char*>(&x), sizeof(x));
		infile.read(reinterpret_cast<char*>(&y), sizeof(y));

		rTempSpriteInfo.spriteName = rSprName;
		rTempSpriteInfo.spriteLocation = rSpriteLoc;
		rTempSpriteInfo.w = w;
		rTempSpriteInfo.h = h;
		rTempSpriteInfo.x = x;
		rTempSpriteInfo.y = y;

		rTempSpriteInfoVec.push_back(rTempSpriteInfo);
	}
	infile.close();

	std::cout << std::endl;
	std::cout << "######### SAVE INFORMATION #########" << std::endl;
	std::cout << "Save version: " << rSaveVer << " Current Save Version: " << rSaveVer << std::endl;
	std::cout << "Script path: " << rScriptLoc << std::endl;
	std::cout << "Script line number: " << rScriptLine << std::endl;
	std::cout << "Background path: " << rBacLoc << std::endl;
	std::cout << "######### CHARACTERS #########" << std::endl;
	for (int i = 0; i < rNumChar; ++i) {
		std::cout << "Character name: " << rTempSpriteInfoVec.at(i).spriteName << std::endl;
		std::cout << "Character sprite: " << rTempSpriteInfoVec.at(i).spriteLocation << std::endl;
	}

	saveData.scriptPath = rScriptLoc;
	saveData.scriptLine = rScriptLine;
	saveData.backgroundPath = rBacLoc;
	saveData.sprites = rTempSpriteInfoVec;

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