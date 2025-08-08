#include "Interpreter.h"

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

void Interpreter::JumpToChoice(std::string choice) {
	std::cout << "clicked " << choice << "\n";
}

void Interpreter::Run(SDL_Event e, SpriteManager& _spriteManager, TextManager& _textManager, UIManager& _uiManager, Texture& background) {
	// currently no way to check if we reach the end of the file, so it just crashes
	// what do the do in vn engines? idrk

	if (_lineCount >= _scriptFile.size()) {
		return; // dunno what to do now that we've reached the end of file... just sit there?
	}

	_commandArgs.clear();

	std::regex splitRegex(R"(".*?\"|\S+)");
	std::string cTokens = _scriptFile[_lineCount];
	auto tokens_begin = std::sregex_iterator(cTokens.begin(), cTokens.end(), splitRegex);
	auto tokens_end = std::sregex_iterator();

	for (std::sregex_iterator i = tokens_begin; i != tokens_end; ++i) {
		std::smatch mToken = *i;
		_commandArgs.push_back(mToken.str());
	}
	//_commandArgs = splitString(_scriptFile[_lineCount]);

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
		// clean all this shit up bro...
		if (!increment) { return; }

		std::string btnName;
		std::string btnContents;

		int numButtons = 0;

		// remove magic numbers...

		try {
			numButtons = std::stod(_commandArgs[1]);
		}
		catch (std::invalid_argument ia) {
			PrintError(ia.what());
			return;
		}

		int startY = (numButtons > 1 ? SCREEN_HEIGHT / numButtons : SCREEN_HEIGHT / 2);

		for (int i = 2; i <= numButtons * 2; i++) {
			btnName = _commandArgs[i];
			btnContents = _commandArgs[i + 1];
			btnContents = btnContents.substr(1, (btnContents.length() - 2) );

			_uiManager.AddButton(btnName, btnContents, 
				(SCREEN_WIDTH / 2) - (CHOICE_BUTTON_WIDTH/2) , startY - CHOICE_BUTTON_HEIGHT, 
				CHOICE_BUTTON_WIDTH, CHOICE_BUTTON_HEIGHT);
			startY += CHOICE_BUTTON_HEIGHT + (CHOICE_BUTTON_HEIGHT/2);
			i++; // NEED TO MAKE SURE WE SKIP OVER THE BUTTON TXT FOR THE CURRENT BUTTON
		}

		// what are we doing here?
		// In button.h we have defined an std::function OnClick()
		// this is because we want to be able to copy different functions to it.
		// why?
		// So we can have multiple buttons that do different things...
		// example fast forward button to skip text, pause button, choice button
		// so when a button is created, it needs a function assigned.
		// to do that we use a lambda, this allows us to pass the function not as
		// a result but to say "use this function when OnClick for this button is called"
		// this means we can also let any potentiol arguments go through for each button

		for (auto btn : _uiManager.GetUiVector()) {
			// Could use [=] for lambda capture, but all lambda might capture the 
			// last pointer value of the button, so we just want the string on its own.
			std::string btnName = btn->GetButtonName(); 
			btn->OnClick = [this, btnName]() { JumpToChoice(btnName); };
		}

		// when button is clicked:
		//	interpreter fires function JUMPTOEVENT(STRING btnName)
		//  uses the button name 
		//	store this function into the onclick function? so it gets fired by the button?
		// using callbacks?

		increment = false;

		// need to pause input for choice selection, then resume once its made
	}

	else if (_commandArgs[0] == "*setbackground") {
		background.loadFromFile(GLOBAL_BACKGROUNDS_PATH + _commandArgs[1]);

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


	// think of input
	// we read a line and check the command
	// for pretty much everything we want to execute it and move onto the next command
	// however for special cases like choices and text we want to print them to the screen
	// and then wait for user input before continuing...

	// once we have our command, read next line
	if (increment) {
		_lineCount++;
	}
	
}
