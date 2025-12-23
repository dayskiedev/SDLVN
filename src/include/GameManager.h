#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include <memory>

#include "Config.h"

// managers
#include "SaveManager.h"
#include "AudioManager.h"
#include "UIManager.h"

// states
#include "Menu.h"
#include "Game.h"
#include "Load.h"

class GameManager {
public:
	bool Init();
	void Run();
	void Quit();

	void RequestState(std::unique_ptr<GameState> state);

	bool SaveExists(std::string savePath);

	SaveManager::SaveData& GetSaveData() { return saveData; }

	void LoadSave(std::string savePath);

	void QuickSave();
	void SaveGame(std::string savePath);
	void DeleteSave(std::string savePath);
	void DeleteAllSaves(std::string savePath);
	
	void SetSaveReferences(std::shared_ptr<Interpreter> interpreterInfo, std::shared_ptr<SpriteManager> spriteManagerInfo, std::shared_ptr<Sprite> background);

	void SetDefaultGameState() { saveData = {}; }

	void PrintCurrentSaveData();

	AudioManager* GetAudioManager() { return &audioManager; }

	bool running = true;

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
	std::unique_ptr<SaveManager> saveManager;

	// data for saving
	std::shared_ptr<Interpreter> _interpreterInfo;
	std::shared_ptr<SpriteManager> _spriteManagerInfo;
	std::shared_ptr<Sprite> _background;

	std::unique_ptr<GameState> currentState;
	std::unique_ptr<GameState> pendingState;

	// value member?
	AudioManager audioManager;

};
