#include "SaveLoadUI.h"
#include "GameManager.h"

SaveLoadUI::SaveLoadUI() {}

void SaveLoadUI::LoadSaveLoadUI(SDL_Renderer* renderer, GameManager* gameManager) {
	_gameManager = gameManager;
	std::shared_ptr<Texture> background = std::make_shared<Texture>(renderer, GLOBAL_BACKGROUNDS_PATH + "saveload_background.png", SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	slBackButton = std::make_shared<Button>("optionsBack", Button::UI, renderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 0, 0, "Back", 30);

	saveLoadUIBaseVec.push_back(background);
	saveLoadUIBaseVec.push_back(slBackButton);

	int cols = 3;
	int rows = 2;

	// will change depending on selection
	int saveIndex = 0;

	// he we create a 2*3 grid of save icons that the users can select from to load a save
	// the save index will match the name of save files created, so we can have as many saves
	// as we want, just need to create a row selector to cycle between saves and set the buttons
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::string savefileButtonTexture = DEFAULT_BUTTON_TEXTURE;
			std::string saveName = "save" + std::to_string(saveIndex);
			std::string saveDirectory = DEFAULT_SAVE_LOCATION + saveName + ".dat";

			// for some reason i could still use filesystem even when i removeed the header??
			bool saveExists = _gameManager->SaveExists(saveDirectory);

			if (saveExists) {
				savefileButtonTexture = saveExistsTexturePath;
			}

			// if this save exists in save directory, then we want the icon to be the save img
			// using raw values for ui is bad i know
			std::shared_ptr<Button> loadSaveButton(new Button(saveName,Button::UI, renderer, savefileButtonTexture, 250, 250, 100 + (400 * j), 75 + (275 * i) ));
			saveLoadUIBaseVec.push_back(loadSaveButton);
			saveIndex++;
		}
	}

	
}


// need to dynamic cast because c++ doesnt just have a check obj type ig?
void SaveLoadUI::UpdateFileButtons(bool loadMode) {
	for (auto& obj : saveLoadUIBaseVec) {
		// cast obj to button, if obj is null its not a button, then check start of obj name to see if it matches save buttons
		auto b = std::dynamic_pointer_cast<Button> (obj);
		if (b != NULL && b->GetButtonName().substr(0,4) == "save") {
			std::string savePath = DEFAULT_SAVE_LOCATION + b->GetButtonName() + ".dat";

			// if loadmode is true it means we want to load a save when clicked, and the opposite when its false
			if (loadMode) {
				b->OnClick = [this, savePath]() {
					_gameManager->LoadSave(savePath);
				};
			}
			else {
				b->OnClick = [this, b, savePath]() {
					b->ChangeTexture(saveExistsTexturePath);
					_gameManager->SaveGame(savePath);
				};
			}

		}
	}
}

void SaveLoadUI::AddObject(std::shared_ptr<Texture> obj) {
	saveLoadUIBaseVec.push_back(obj);
}

void SaveLoadUI::UpdateSaveFiles() {
	// update textures of save if save file exists?
}