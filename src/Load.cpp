#include "Load.h"

void Load::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	_gameManager = gameManager;
	loadRenderer = renderer;

	loadUI = std::make_unique<UIManager>();
	loadUI->setRenderer(loadRenderer);

	std::shared_ptr<Button> backButton(new Button("back",
		Button::UI,
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


	// he we create a 2*3 grid of save icons that the users can select from to load a save
	// the save index will match the name of save files created, so we can have as many saves
	// as we want, just need to create a row selector to cycle between saves and set the buttons
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::string savefileButtonTexture = DEFAULT_BUTTON_TEXTURE;
			std::string saveName = "save" + std::to_string(saveIndex);
			std::string saveDirectory = DEFAULT_SAVE_LOCATION + saveName + ".dat";

			// for some reason i could still use filesystem even when i removeed the header??
			bool saveExists = gameManager->SaveExists(saveDirectory);

			if (saveExists) {;
				savefileButtonTexture = GLOBAL_SPRITES_PATH + "saveExists.png";
				saveName = "";
			}

			// if this save exists in save directory, then we want the icon to be the save img
			// using raw values for ui is bad i know
			std::shared_ptr<Button> loadSaveButton(new Button("save",
				Button::UI,
				loadRenderer,
				savefileButtonTexture,
				250, 250,
				100 + (400 * j),
				75 + (275 * i)
			));

			if (saveExists) {
				// i know its silly to check again but we need to in order to properly assign the onClick functions
				loadSaveButton->OnClick = [this, saveIndex, saveDirectory]() { 
					std::cout << "Loading save " << std::to_string(saveIndex) << std::endl,
					_gameManager->LoadSave(saveDirectory),
					_gameManager->ChangeState(std::make_unique<Game>());
					};
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
		b->Render();
		// why is this seperate lol?
		b->showText();
	}

	SDL_RenderPresent(loadRenderer);
}

void Load::Update(SDL_Event e, double deltaTime) {
	for (auto b : loadUI->GetUiVector()) { b->Update(e); }
}

void Load::ExitState() {
	loadRenderer = NULL;
	_gameManager = NULL;
	loadUI.reset();
}
