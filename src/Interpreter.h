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
#include <regex>
#include <functional>

#include "SpriteManager.h"
#include "TextManager.h"
#include "UIManager.h"

#include "Config.h"

class Interpreter {
public:
	bool OpenScript(std::string scriptPath);

	void PrintError(std::string Error);

	// pass by referecne because we want to modify the sprites/text in these vectors
	void Run(SDL_Event e, double deltaTime, SpriteManager& _spriteManager, TextManager& _textManager, UIManager& _uiManager, Texture& background);

	void JumpToChoice(std::string choice);
	void ButtonClicked();

	void TokenizeLine();

	bool ArgCheckSize(int expected, int actual);
private:
	std::string spriteObjName;
	std::string spriteTexName;
	std::string spritePosition;

	int _lineCount = 0; //temp value, will be replaced with script loading
	bool increment = true;
	bool incrementText = false;

	Text* curDialogueLine;
	// vns file:
	// type: MAIN -- entry point for file
	// data: path/to/data vn title, dialouge selections
	std::vector<std::string> _scriptFile;
	std::vector<std::string> _commandArgs;

	double textSpeed	= DEFAULT_TEXT_SPEED;
	double textCounter	= 0;
	double threshold	= 50 / textSpeed;

	UIManager* _uiManager;
};