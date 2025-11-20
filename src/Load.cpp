#include "Load.h"

void Load::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	_gameManager = gameManager;
	loadRenderer = renderer;

	loadUI = std::make_unique<UIManager>();
	loadUI->setRenderer(loadRenderer);

	saveManager = std::make_unique<SaveManager>();

	for (auto save : saveManager->ScanForSaves()) {
		std::cout << save << std::endl;
	}

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

	// save screenshot of save to seperate thumbnails folder matching that save name
	int cols = 3;
	int rows = 3;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			std::shared_ptr<Button> loadSaveButton(new Button("save",
				loadRenderer,
				DEFAULT_BUTTON_TEXTURE,
				200, 50,
				200 + (270 * j),
				200 + (70 * i),
				"load save",
				25
			));

			loadUI->AddButton(loadSaveButton);

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
