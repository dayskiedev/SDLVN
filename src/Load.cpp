#include "Load.h"

void Load::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	_gameManager = gameManager;
	loadRenderer = renderer;

	loadUI = std::make_unique<UIManager>();
	loadUI->setRenderer(loadRenderer);

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
	// placeholder
}
