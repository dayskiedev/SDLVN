#include "Interpreter.h"

std::vector<std::string> Interpreter::splitString(std::string s) {
	std::stringstream ss(s);
	std::string arg;
	std::vector<std::string> args;

	while (ss >> arg) {
		args.push_back(arg);
	}

	return args;
}

void Interpreter::PrintError(std::string Error) {
	std::cout << "Error on line " << -_lineCount + 1 << ": ";
	std::cout << Error << std::endl;

	// do i need this function? Not so sure to be honest....
}

void Interpreter::Run(SDL_Event e, SpriteManager& _spriteManager, TextManager& _textManager) {

	if (exampleCommandLine[_lineCount].empty()) { 
		PrintError("No arguments found on this line! pausing...");
		increment = false;
		return; // exits run, but since run is in a loop it will be called again, on the new line
	}
	_commandArgs = splitString(exampleCommandLine[_lineCount]);	
	// for security assume every thing that isn't caught by the commands
	// checks is text, although what if we want to define special features
	// for the text? position, etc we'll deal with that later..

	// a the end of the loop we check if input is paused, if not we
	// increment the command, this lets us hang on text, or delays etc...

	// error checking will only relate to arguments
	// we do not care about the contents of the arguments,
	// they will be handled by the objects themselves
	// we only care if the argument is there, and it matches the 
	// formatting / type required (which 99% of will be string)

	if (_commandArgs[0] == "*enter") {
		// some sort of arg checker 
		spriteObjName	= _commandArgs[1];
		spriteTexName	= _commandArgs[2];
		spritePosition	= _commandArgs[3];
		_spriteManager.addSprite(spriteObjName, spriteTexName, spritePosition);
	}
	
	else if (_commandArgs[0] == "*exit") {
		spriteObjName = _commandArgs[1];
		_spriteManager.removeSprite(spriteObjName);
	}

	else if (_commandArgs[0] == "*setsprite") {
		spriteObjName = _commandArgs[1];
		spriteTexName = _commandArgs[2];

		_spriteManager.setSprite(spriteObjName, spriteTexName);
	}

	else if (_commandArgs[0] == "*cleartext") {
		_textManager.clearText();
	}
	// JUST PRINT IT TO THE SCREEN IDK
	// add support for stuff like \n 
	else {
		if (increment) {
			//print to screen
			_textManager.addText(exampleCommandLine[_lineCount]);
			increment = false;
		}

		// print text to screen, THEN INCREMENT TO NEXT LINE AFTER
		// SPACE PRESS!
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_SPACE:
				increment = true;
			}
		}
	}

	// once we have our command, read next line
	if (increment) {
		_lineCount++;
	}
	
}