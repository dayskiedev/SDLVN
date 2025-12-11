#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Config.h"
#include "Texture.h"
#include "Button.h"
#include "Sprite.h"

// rememebr that include basically copy pastes the code that we will need to use
// this can lead to circular inclusions (ie what was happening here, gamemanager
// includes menu and menu include saveloadui which includes gamemanger etc etc
// headers only declare things, cpp files define them
class GameManager;

class SaveLoadUI{
public:
	SaveLoadUI();

	void LoadSaveLoadUI(SDL_Renderer* renderer, GameManager* gameManager);
	void AddObject(std::shared_ptr<Texture> obj);
	std::vector< std::shared_ptr<Texture>> getVector() { return saveLoadUIBaseVec; }

	std::shared_ptr<Button> GetBackButton() { return slBackButton; }

	// set to true = we want to load a save, set to false = we want to create a save
	bool setLoadMode(bool m) { loadMode = m; }

	void UpdateFileButtons(bool loadMode);

	void UpdateSaveFiles();
private:
	std::vector<std::shared_ptr<Texture>> saveLoadUIBaseVec;

	std::shared_ptr<Button> slBackButton;
	GameManager* _gameManager;
	bool loadMode = false;
};