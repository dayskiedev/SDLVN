#include "SaveManager.h"

// dump game memory into binary and load that?


// SAVE STRUCTURE:
// SAVE VERSION
// SCRIPT LOCATION
// SCRIPT LINE (THEN WE WILL AUTO READ THE LINE)
// BACKGROUND TO LOAD
// [CHARACTERS]
// CHARACTERS TO LOAD (name, path to cur sprite)
// [CHOICES]
// SET EVERY SAVED CHOICE

void SaveManager::Save() {
	std::cout << "Saving file to " << DEFAULT_SAVE_LOCATION << std::endl;

	std::ofstream outfile(DEFAULT_SAVE_LOCATION + "binary.txt", std::ofstream::binary);

	//std::string text = ("testingsave");
	//size = text.size();

	//outfile.write(reinterpret_cast<char *>(&size), sizeof(size));
	//outfile.write(text.c_str(), text.size());
	// we need to tell the binary file what we are writing to it, and how big it is (the point of sizeof)
	
	std::string scriptLoc = "script location";
	int scriptLine = 12;
	std::string backgroundLoc = "background/directory.png";

	// will be a loop
	std::string characterName = "lucio";
	std::string characterSprite = "sprites/lucio_mad.png";

	// also a loop
	std::string choiceName = "PEEEEENIIIISS";
	int choiceValue = 1; // flipped

	unsigned int size;

	outfile.write(reinterpret_cast<const char*>(&SAVE_VERSION), sizeof(SAVE_VERSION));	// SAVE VERSION

	size = scriptLoc.size(); // string does not store its size in binary so we write it
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// SCRIPT SAVE LOC
	outfile.write(scriptLoc.c_str(), sizeof(scriptLoc));

	outfile.write(reinterpret_cast<const char*>(&scriptLine), sizeof(scriptLine));		// SCRIPT LINE NUMBER	

	size = backgroundLoc.size(); 
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// BACKGROUND DIRECTORY LOCATION
	outfile.write(backgroundLoc.c_str(), sizeof(backgroundLoc));

	// CHARACTER DATA
	size = characterName.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// CHARACTER NAME
	outfile.write(characterName.c_str(), sizeof(characterName));

	size = characterSprite.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// CHARACTER SPRITE DIRECTORY LOCATION
	outfile.write(characterSprite.c_str(), sizeof(characterSprite));

	// CHOICE DATA
	size = choiceName.size();
	outfile.write(reinterpret_cast<char*>(&size), sizeof(size));						// CHOICE NAME
	outfile.write(choiceName.c_str(), sizeof(choiceName));

	outfile.write(reinterpret_cast<const char*>(&choiceValue), sizeof(choiceValue));	// SCRIPT LINE NUMBER

	outfile.close();
}

void SaveManager::Load() {
	std::cout << "Loading " << DEFAULT_SAVE_LOCATION << "binary.txt" << std::endl;
	std::ifstream infile(DEFAULT_SAVE_LOCATION + "binary.txt", std::ifstream::binary);
	if (!infile.is_open()) {
		std::cout << "Failed to open file!" << std::endl;
		return;
	}

	// READING IN GAME DATA
	int rSaveVer = 0;
	std::string rScriptLoc;
	int rScriptLine = 0;
	std::string rBacLoc;
	std::string rCharName;
	std::string rCharSpriLoc;
	std::string rChoiceName;
	int rChoiceValue;

	infile.read(reinterpret_cast<char*>(&rSaveVer), sizeof(rSaveVer));

	// safety check for saves, because we may change the save layout we want to change this (should be removed in final ver)
	if (rSaveVer != SAVE_VERSION) {
		std::cout << "Error: mismatched save version, read: " << rSaveVer << " when current version is: " << SAVE_VERSION << std::endl;
		return;
	}

	int rfileSize = 0;
	infile.read(reinterpret_cast<char*>(&rfileSize), sizeof(rfileSize));

	infile.close();

	std::cout << "save version: " << rSaveVer << " game file size: " << rfileSize << std::endl;

}