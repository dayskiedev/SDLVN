#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_timer.h>

#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "SpriteManager.h"
#include "TextManager.h"

class Interpreter {
public:

	// will be moved to a seperate helper functions file possibly
	std::vector<std::string> splitString(std::string s);

	bool OpenScript(std::string scriptPath);

	void PrintError(std::string Error);

	// pass by referecne because we want to modify the sprites/text in these vectors
	void Run(SDL_Event e, SpriteManager& _spriteManager, TextManager& _textManager);


private:
	std::string spriteObjName;
	std::string spriteTexName;
	std::string spritePosition;

	int _lineCount = 0; //temp value, will be replaced with script loading
	bool increment = true;

	// vns file:
	// type: MAIN -- entry point for file
	// data: path/to/data vn title, dialouge selections
	std::vector<std::string> _scriptFile;

	std::vector<std::string> _commandArgs;
};