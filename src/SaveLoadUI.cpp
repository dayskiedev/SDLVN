#include "SaveLoadUI.h"
#include "GameManager.h" 

SaveLoadUI::SaveLoadUI() {}

void SaveLoadUI::LoadSaveLoadUI(SDL_Renderer* renderer, GameManager* gameManager) {
	_gameManager = gameManager;

	std::shared_ptr<Texture> background = std::make_shared<Texture>(renderer, GLOBAL_BACKGROUNDS_PATH + "saveload_background.png", SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	std::shared_ptr<Sprite> uma = std::make_shared<Sprite>("uma", GLOBAL_SPRITES_PATH + "saveicon.png", (SCREEN_WIDTH / 2) - 150, SCREEN_HEIGHT - 300, 300, 300, renderer);
	slBackButton = std::make_shared<Button>("optionsBack", Button::UI, renderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 0, 0, "Back", 30);

	saveLoadUIBaseVec.push_back(background);
	saveLoadUIBaseVec.push_back(uma);
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
				;
				savefileButtonTexture = GLOBAL_SPRITES_PATH + "saveExists.png";
				saveName = "";
			}

			// if this save exists in save directory, then we want the icon to be the save img
			// using raw values for ui is bad i know
			std::shared_ptr<Button> loadSaveButton(new Button("save",Button::UI, renderer, savefileButtonTexture, 250, 250, 100 + (400 * j), 75 + (275 * i) ));


			// needs to check button name....
			// also needs to change depending on save/load mode
			if (saveExists) {
				// i know its silly to check again but we need to in order to properly assign the onClick functions
				loadSaveButton->OnClick = [this, saveIndex, saveDirectory]() {
					std::cout << "Loading save " << std::to_string(saveIndex) << std::endl,
						_gameManager->LoadSave(saveDirectory),
						_gameManager->RequestState(std::make_unique<Game>());
					};
			}
			else {
				loadSaveButton->OnClick = [this, saveIndex]() { std::cout << "No save found..." << std::endl; };
			}

			saveLoadUIBaseVec.push_back(loadSaveButton);
			saveIndex++;
		}
	}

	
}

void SaveLoadUI::AddObject(std::shared_ptr<Texture> obj) {
	saveLoadUIBaseVec.push_back(obj);
}

void SaveLoadUI::UpdateSaveFiles() {
	// update textures of save if save file exists?
}