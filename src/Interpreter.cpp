#include "Interpreter.h"

// have compiler to scroll through uncompiled script

bool Interpreter::Initialise(std::shared_ptr<SpriteManager> sm, std::shared_ptr<TextManager> tm,
							std::shared_ptr<UIManager> uim, std::shared_ptr<Sprite> bg,
	int lineNum, std::string scriptPath, std::string backgroundPath, std::vector<SpriteInformation> sprites) {

	_spriteManager = sm;
	_textManager = tm;
	_uiManager = uim;
	background = bg;

	// loading info should be:
	// load script
	// line to start at
	// whatever background is needed
	// whatever sprite is needed

	_curScript = scriptPath;
	if (!OpenScript(_curScript)) { return false; } // load script 

	_lineCount = lineNum; // line to start script at.

	std::cout << "line count: " << _lineCount << std::endl;
	background->loadFromFile(backgroundPath); // set background to whatever was saved;
	background->SetSpritePath(backgroundPath);

	// load any sprites saved in file
	for (auto curSprite : sprites) {
		_spriteManager->addSprite(curSprite.spriteName,
			curSprite.spriteLocation,
			curSprite.x, curSprite.y,
			curSprite.w, curSprite.h);
	}
	return true;
}

bool Interpreter::OpenScript(std::string filePath) {
	_scriptFile.clear();

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
	int _lineCountInitial = _lineCount;

	while (_lineCount < _scriptFile.size()) {
		if (_scriptFile[_lineCount] == ":" + choice) {
			std::cout << "Reached choice '" << choice << "' on line: " << _lineCount + 1 << "\n";
			ButtonClicked();
			return;
		}
		else { _lineCount++; }
	}

	PrintError("ERROR: Choice " + choice + " not found!");
	_lineCount = _lineCountInitial;
	return;
}

bool Interpreter::ArgCheckSize(int expected, int actual) {
	if (actual < expected) {
		std::cout << "Error: Invalid Arg size! Expected: " << expected << ") Actual: (" << actual << ")" << std::endl;
		return false;
	}
	return true;
}

void Interpreter::ButtonClicked() {
	_lineCount++; // rollover so we dont print the choice
	increment = true;
}

void Interpreter::TokenizeLine() {
	_commandArgs.clear();
	// regex to select
	std::regex splitRegex(R"(".*?\"|\S+)");
	std::string cTokens = _scriptFile[_lineCount];
	auto tokens_begin = std::sregex_iterator(cTokens.begin(), cTokens.end(), splitRegex);
	auto tokens_end = std::sregex_iterator();

	for (std::sregex_iterator i = tokens_begin; i != tokens_end; ++i) {
		std::smatch mToken = *i;
		_commandArgs.push_back(mToken.str());
	}
}

void Interpreter::Run(SDL_Event e, double deltaTime) {

	// here we pass a reference to the ui manager in order to add elements to
	// the screen depending on whats read from the script.

	if (_lineCount >= _scriptFile.size()) { 
		return; // dunno what to do now that we've reached the end of file... just sit there?
	}

	if (_scriptFile[_lineCount].empty()) {
		_lineCount++;
		return;
	}

	if (increment) { TokenizeLine(); }

	// this whole command file needs to be updated

	if (_commandArgs[0] == "#") { increment = true; }

	else if (_commandArgs[0] == "*enter") {
		// *enter [objName] [sprName] [position]
		// some sort of arg checker 
		spriteObjName	= _commandArgs[1];
		spriteTexName	= _commandArgs[2];
		spritePosition = ""; // DEFAULT

		if (_commandArgs.size() > 3) {
			spritePosition = _commandArgs[3];
		}
		_spriteManager->addSprite(spriteObjName, spriteTexName, spritePosition);
	}
	
	else if (_commandArgs[0] == "*exit") {
		spriteObjName = _commandArgs[1];
		_spriteManager->removeSprite(spriteObjName);
	}

	else if (_commandArgs[0] == "*setsprite") {
		// *setsprite [objName] [sprName] [position]
		spriteObjName = _commandArgs[1];
		spriteTexName = _commandArgs[2];

		_spriteManager->setSprite(spriteObjName, spriteTexName);
		
	}

	else if (_commandArgs[0] == "*cleartext") {
		_textManager->clearText();
	}

	else if (_commandArgs[0] == "*wait") {
		// *wait [time_to_wait]
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
		// this should all be movied to ui manager i think....
		// *choice [num_choices] [btnName] [btnContents] ,,, can extend further
		if (!increment) { return; }

		std::string btnName;
		std::string btnContents;

		int numButtons = 0;

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
			btnContents = btnContents.substr(1, (btnContents.length() - 2));

			std::shared_ptr<Button> choiceButton(new Button(btnName,
				Button::CHOICE,
				_uiManager->getRenderer(),
				DEFAULT_BUTTON_TEXTURE,
				CHOICE_BUTTON_WIDTH,
				CHOICE_BUTTON_HEIGHT,
				(SCREEN_WIDTH / 2) - (CHOICE_BUTTON_WIDTH / 2),
				startY - CHOICE_BUTTON_HEIGHT,
				btnContents,
				30
			));

			choiceButton->OnClick = [this, btnName]() { 
				JumpToChoice(btnName),
				_uiManager->RemoveButtonsByType(Button::CHOICE);
			};

			_uiManager->AddButton(choiceButton);
			startY += CHOICE_BUTTON_HEIGHT + (CHOICE_BUTTON_HEIGHT / 2);
			i++; // NEED TO MAKE SURE WE SKIP OVER THE BUTTON TXT FOR THE CURRENT BUTTON
		}

		increment = false;

		// need to pause input for choice selection, then resume once its made
	}

	else if (_commandArgs[0] == "*reply") {
		// reply [reply text]
		if (!increment) { return; }
		std::string replyContents = _commandArgs[1];
		replyContents = replyContents.substr(1, (replyContents.length() - 2));

		std::shared_ptr<Button> replyButton(new Button("reply",
			Button::REPLY,
			_uiManager->getRenderer(),
			DEFAULT_BUTTON_TEXTURE,
			CHOICE_BUTTON_WIDTH,
			CHOICE_BUTTON_HEIGHT,
			(SCREEN_WIDTH / 2) - (CHOICE_BUTTON_WIDTH / 2),
			(SCREEN_HEIGHT / 2) - (CHOICE_BUTTON_HEIGHT / 2),
			replyContents,
			30
		));
		replyButton->OnClick = [this]() { 
			ButtonClicked(),
			_uiManager->RemoveButtonsByType(Button::REPLY);
		};
		_uiManager->AddButton(replyButton);

		// wait for input
		increment = false;
	}

	else if (_commandArgs[0] == "*setbackground") {
		// *setbackackground [background_path]
		if (!ArgCheckSize(2, _commandArgs.size())) { return; }
		background->loadFromFile(GLOBAL_BACKGROUNDS_PATH + _commandArgs[1]);
		background->SetSpritePath(GLOBAL_BACKGROUNDS_PATH + _commandArgs[1]);

	}

	else if (_commandArgs[0] == "*jumpto") {
		std::string choice = _commandArgs[1];
		JumpToChoice(choice);
	}

	// jumptoline command
	// playmusic command
	// pause music command
	// stop music command

	// textspeed command
	// *textspeed [double]

	else {
		if (increment) {
			curDialogueLine = _textManager->addText(_scriptFile[_lineCount]);
			incrementText = true;
			increment = false;

		}
		if (incrementText) {
			if (curDialogueLine->GetCurTextLength() >= curDialogueLine->GetTextLength()) {
				incrementText = false;
				return;
			}
			
			// smooth text update per frame without interuptting other actions
			if (textCounter >= threshold) {
				// if we have passed or reached the text threshold, render the next character
				curDialogueLine->SetCurTextLength(curDialogueLine->GetCurTextLength() + 1); // try out overload operators?
				textCounter = 0;
			}
			// otherwise increase the textcounter, deltatime keeps the text incremementing at the same 
			// speed every update by increasing the increment by the amount of times between frames
			// if there is a long gap between frames, deltatime is large, meaning the increment increases quicker 
			// reaching the threshold quicker allowing for smooth text updates
			else { textCounter += deltaTime; }


		}

		// print text to screen, gTHEN INCREMENT TO NEXT LINE AFTER
		// SPACE PRESS!
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_SPACE:
				if (curDialogueLine->GetCurTextLength() < curDialogueLine->GetTextLength() - 1) {
					curDialogueLine->SetCurTextLength(curDialogueLine->GetTextLength());
					incrementText = false;

					// if we don't return we will instantly skip to the next line in the
					// interpretor which we dont want
					return;
				}
				else {
					increment = true;
				}
				break;
			}
		}
	}

	if (increment) {
		_lineCount++;
	}
	
}

std::string Interpreter::GetCurrentScript() { return _curScript; }
int Interpreter::GetCurrentScriptLine() { return _lineCount; }
