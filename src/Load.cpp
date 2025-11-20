#include "Load.h"

void Load::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	_gameManager = gameManager;
	loadRenderer = renderer;

	loadUI = std::make_unique<UIManager>();
	loadUI->setRenderer(loadRenderer);

	saveManager = std::make_unique<SaveManager>();

	std::shared_ptr<Button> backButton(new Button("back",
		loadRenderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		0, 0,
		"Back to Menu",
		25
	));


	// volume slider
	// simple box that can be dragged
	// lock y axis, set limit on x axis

	// maybe should be added as soon as we make the button?
	backButton->OnClick = [this]() { _gameManager->ChangeState(std::make_unique<Menu>()); };
	loadUI->AddButton(backButton);


	// loop for creating save buttons

	// 6 * 5 saves
	// buttons will load first 6 saves
	// read save position from saves?
	// save slot == 0;

	// save name could match slot? then we only need to 
	// search inside the folder for the saves that match the 
	// current page:
	// 0-5 6-11 and so on
	// then if we find the corresponding save, we can assign the save to the created button
	// alongside its screenshot

	// confirmation selector
	//		pops up to cinfirm option
	//      if no just delete popup
	//      if yes call whatever function you wanted to call (double passthrough?)

	// choice selector
	//		row of buttons 1-n
	//		option to select multiple or only 1
	//		returns what button is selected

	// save screenshot of save to seperate thumbnails folder matching that save name
	int cols = 3;
	int rows = 2;

	// will change depending on selection
	int saveIndex = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::string savefileButtonTexture = DEFAULT_BUTTON_TEXTURE;
			std::string saveName = "save" + std::to_string(saveIndex);

			// for some reason i could still use filesystem even when i removeed the header??
			bool saveExists = saveManager->SaveExists(DEFAULT_SAVE_LOCATION + saveName + ".dat");

			if (saveExists) {;
				savefileButtonTexture = GLOBAL_SPRITES_PATH + "saveExists.png";
				saveName = "";
			}

			// if this save exists in save directory, then we want the icon to be the save img
			// using raw values for ui is bad i know
			std::shared_ptr<Button> loadSaveButton(new Button("save",
				loadRenderer,
				savefileButtonTexture,
				250, 250,
				100 + (400 * j),
				75 + (275 * i)
			));

			if (saveExists) {
				// i know its silly to check again but we need to in order to properly assign the onClick functions
				loadSaveButton->OnClick = [this, saveIndex]() { std::cout << "Loading save " << std::to_string(saveIndex) << std::endl; };
			}
			else {
				loadSaveButton->OnClick = [this, saveIndex]() { std::cout << "No save found..." << std::endl; };
			}

			loadUI->AddButton(loadSaveButton);
			saveIndex++;
		}
	}

}

void Load::Render() {
	SDL_SetRenderDrawColor(loadRenderer, 100, 100, 100, 100);
	SDL_RenderClear(loadRenderer);

	for (auto b : loadUI->GetUiVector()) {
		b->render();
		// why is this seperate lol?
		b->showText();
	}

	SDL_RenderPresent(loadRenderer);
}

void Load::Update(SDL_Event e, double deltaTime) {
	for (auto b : loadUI->GetUiVector()) { b->Update(e); }
}

void Load::ExitState() {
	loadUI.reset();
}
