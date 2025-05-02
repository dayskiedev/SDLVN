#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>

#include <iostream>
#include <sstream>
#include <vector>

#include "SpriteManager.h"
#include "TextManager.h"

class Interpreter {
public:

	// will be moved to a seperate helper functions file possibly
	std::vector<std::string> splitString(std::string s);

	void PrintError(std::string Error);

	// pass by referecne because we want to modify the sprites/text in these vectors
	void Run(SDL_Event e, SpriteManager& _spriteManager, TextManager& _textManager);

private:
	std::string spriteObjName;
	std::string spriteTexName;
	std::string spritePosition;

	int _lineCount = 0; //temp value, will be replaced with script loading
	bool increment = true;

	std::vector<std::string> _commandArgs;
	std::string exampleCommandLine[50] = {
	"*enter saber saber.png CENTRE",
	"So, what am I doing here exactly?",
	"Hurry up and say something!",
	"*setsprite saber saber4.png",
	"*enter rin rin.png CENTRE",
	"hiiiii saber",
	"*exit saber",
	"ok rude",
	"*setsprite rin rin2.png",
	"She didn't even say hi back...",
	"*setsprite rin rin3.png",
	"Did I do something to make her mad?",
	"*exit rin"
	};
};