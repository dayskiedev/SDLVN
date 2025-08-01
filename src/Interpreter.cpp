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

bool Interpreter::OpenScript(std::string filePath) {
	_scriptFile.empty();

	if (std::filesystem::path(filePath).extension() != ".vns") {
		std::cout << "Incorrect file format! (Must be a .vns file.)\n";
		return false;
	}

	std::ifstream _scriptFileRaw(filePath);

	if (!_scriptFileRaw.is_open()) {
		PrintError("Unable to open file: " + filePath);
		return false;
	}

	std::cout << "Opened file" << filePath << std::endl;

	std::string line;
	while (std::getline(_scriptFileRaw, line)) {
		_scriptFile.push_back(line);
	}
	_scriptFileRaw.close();
	
	std::cout << "Copied file to vector \n";
	return true;
}

void Interpreter::PrintError(std::string Error) {
	std::cout << "Error on line " << _lineCount + 1 << ": ";
	std::cout << Error << std::endl;

	// do i need this function? Not so sure to be honest....
}

void Interpreter::Run(SDL_Event e, SpriteManager& _spriteManager, TextManager& _textManager, UIManager& _uiManager) {
	// currently no way to check if we reach the end of the file, so it just crashes
	// what do the do in vn engines? idrk

	if (_lineCount >= _scriptFile.size()) {
		return; // dunno what to do now that we've reached the end of file... just sit there?
	}

	_commandArgs = splitString(_scriptFile[_lineCount]);	

	if (_commandArgs[0] == "#") { increment = true; }

	else if (_commandArgs[0] == "*enter") {
		// some sort of arg checker 
		spriteObjName	= _commandArgs[1];
		spriteTexName	= _commandArgs[2];
		spritePosition = ""; // DEFAULT

		if (_commandArgs.size() > 3) {
			spritePosition = _commandArgs[3];
		}
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

	else if (_commandArgs[0] == "*wait") {
		double delayTime = 0;
		try {
			delayTime = std::stod(_commandArgs[1]);
		}
		catch(std::invalid_argument ia) {
			PrintError(ia.what());
			return;
		}

		delayTime *= 1000; //ms to second
		std::cout << "waiting " << delayTime << std::endl;
		SDL_Delay(delayTime);
		std::cout << "wating finished!" << std::endl;
	}

	else if (_commandArgs[0] == "*choice") {
		// choice buttons will have predefined locations
		std::string btnName;
		std::string btnContents;

		int x, y, w, h; // will be defined later so we dont pirate software

		int numButtons = 0;
		int startX = 100;

		try {
			numButtons = std::stod(_commandArgs[1]);
		}
		catch (std::invalid_argument ia) {
			PrintError(ia.what());
			return;
		}

		for (int i = 0; i < numButtons; ++i) {
			btnName = _commandArgs[i + 2];
			_uiManager.AddButton(btnName, "empty", startX, 200, 200, 200);
			startX += 300;
		}

		// needs to be more defined from vns file
		// also a lot of these need default values..c
	}

	else {
		if (increment) {
			//print to screen
			_textManager.addText(_scriptFile[_lineCount]);
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