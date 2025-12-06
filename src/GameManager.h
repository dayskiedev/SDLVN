#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include <memory>

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Config.h"

// managers
#include "SaveManager.h"
#include "UIManager.h"

// states
#include "Menu.h"
#include "Options.h"
#include "Game.h"
#include "Load.h"
#include "PauseUI.h"

class GameManager {
public:
	bool Init();
	void Run();
	void Quit();

	void ChangeState(std::unique_ptr<GameState> state);	

	bool SaveExists(std::string savePath);

	SaveManager::SaveData& GetSaveData() { return saveData; }

	void LoadSave(std::string savePath);

	void QuickSave(Interpreter& interpreterInfo, std::shared_ptr<SpriteManager> spriteManagerInfo, std::shared_ptr<Sprite> background);
	void SaveGame(Interpreter& interpreterInfo, std::shared_ptr<SpriteManager> spriteManagerInfo, std::shared_ptr<Sprite> background);
	
	void SetDefaultGameState() { saveData = {}; }

	void PrintCurrentSaveData();

	bool running = true;
	bool pause;

	SDL_Event e;

	// the window we render to
	SDL_Window* gWindow = NULL;

	// window renderer
	SDL_Renderer* gRenderer = NULL;
private:
	Uint64 NOW = 0;
	Uint64 LAST = 0;

	double deltaTime = 0;
	SaveManager::SaveData saveData;
	std::unique_ptr<GameState> currentState;
	std::unique_ptr<SaveManager> saveManager;
};

#endif