#include "Options.h"

void Options::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	_gameManager = gameManager;
	optionRenderer = renderer;

	optionUi = std::make_unique<UIManager>();
	optionUi->setRenderer(optionRenderer);

	std::shared_ptr<Button> backButton(new Button("back",
		Button::UI,
		optionRenderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		0, 0,
		"Back to Menu",
		25
	));

	std::shared_ptr<Button> eraseButton(new Button("erase",
		Button::UI,
		optionRenderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		(SCREEN_WIDTH / 2 - 100), (SCREEN_HEIGHT / 2) - 25,
		"Erase Data",
		25
	));

	// volume slider
	// simple box that can be dragged
	// lock y axis, set limit on x axis

	// maybe should be added as soon as we make the button?
	backButton->OnClick = [this]() { _gameManager->ChangeState(std::make_unique<Menu>()); };


	optionUi->AddButton(backButton);
	optionUi->AddButton(eraseButton);

}

void Options::Render() {
	SDL_SetRenderDrawColor(optionRenderer, 100, 100, 100, 100);
	SDL_RenderClear(optionRenderer);

	for (auto b : optionUi->GetUiVector()) {
		b->render();
		// why is this seperate lol?
		b->showText();
	}

	SDL_RenderPresent(optionRenderer);
}

void Options::Update(SDL_Event e, double deltaTime) {
	for (auto b : optionUi->GetUiVector()) { b->Update(e); }
}

void Options::ExitState() {
	// placeholder
}
