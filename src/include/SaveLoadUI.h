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

	enum FILE_LOAD_MODE {
		SAVE,
		LOAD,
		DELETE
	};

	void LoadSaveLoadUI(SDL_Renderer* renderer, GameManager* gameManager);
	void AddObject(std::shared_ptr<Texture> obj);
	std::vector< std::shared_ptr<Texture>> getVector() { return saveLoadUIBaseVec; }

	std::shared_ptr<Button> GetBackButton() { return slBackButton; }

	// set to true = we want to load a save, set to false = we want to create a save
	void UpdateFileButtons(FILE_LOAD_MODE flm);

	void UpdateSaveFiles();
private:
	std::vector<std::shared_ptr<Texture>> saveLoadUIBaseVec;

	std::shared_ptr<Button> slBackButton;
	std::shared_ptr<Text> infoText;
	GameManager* _gameManager;

	std::string saveExistsTexturePath = GLOBAL_SPRITES_PATH + "saveExists.png";
};