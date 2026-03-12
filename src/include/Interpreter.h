#pragma once

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
#include <memory>

#include "SpriteManager.h"
#include "SpriteInformation.h"
#include "TextManager.h"
#include "AnimationManager.h"	
#include "UIManager.h"

#include "Config.h"
#include "SaveDataS.h"

class Interpreter {
public:

	bool Initialise(std::shared_ptr<SpriteManager> sm, std::shared_ptr<TextManager> tm, 
					std::shared_ptr<UIManager> uim, AudioManager* audioManager, std::shared_ptr<Sprite> bg, std::shared_ptr<AnimationManager> am, SaveData saveData);
	bool OpenScript(std::string scriptPath);

	std::string GetCurrentScript() { return _curScript; }
	int GetCurrentScriptLine() { return _lineCount; }

	std::string GetCurrentMusicPath() { return _curMusicPath; }
	bool GetMusicPlaying() { return _musPlaying; }

	void Run(SDL_Event e, double deltaTime);

	void JumpToChoice(std::string choice);
	void ButtonClicked();

	void TokenizeLine();

	bool ArgCheckSize(int expected, int actual);
private:
	std::string spriteObjName;
	std::string spriteTexName;
	std::string spritePosition;

	int _lineCount = 0; 
	bool increment = true;
	bool incrementText = false;

	std::shared_ptr<Text> curDialogueLine;
	// vns file:
	// type: MAIN -- entry point for file
	// data: path/to/data vn title, dialouge selections
	std::string _curScript;
	std::vector<std::string> _scriptFile;
	std::vector<std::string> _commandArgs;

	double textSpeed	= DEFAULT_TEXT_SPEED;
	double textCounter	= 0;
	double threshold	= 50 / textSpeed;
	double fadeInSpeed	= 0.15;

	std::string _curMusicPath;
	bool _musPlaying;

	std::shared_ptr<SpriteManager> _spriteManager;
	std::shared_ptr<TextManager> _textManager;
	std::shared_ptr<UIManager> _uiManager; 
	std::shared_ptr<Sprite> background;
	std::shared_ptr<AnimationManager> _animationManager;

	// why did we make this a pointer again?????
	AudioManager* _audioManager;
};
