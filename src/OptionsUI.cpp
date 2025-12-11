#include "OptionsUI.h"

OptionsUI::OptionsUI() {}

void OptionsUI::LoadOptionsUI(SDL_Renderer* renderer) {
	std::shared_ptr<Texture> background = std::make_shared<Texture>(renderer, GLOBAL_BACKGROUNDS_PATH + "pause.png", SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	optBackButton = std::make_shared<Button>("optionsBack", Button::UI, renderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 0, 0, "Back", 30);

	std::shared_ptr<Button> eraseButton(new Button("erase",
		Button::UI,
		renderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		(SCREEN_WIDTH / 2 - 100), (SCREEN_HEIGHT / 2) - 25,
		"Erase Data",
		25
	));

	optionsUIBaseVec.push_back(background);
	optionsUIBaseVec.push_back(eraseButton);
	optionsUIBaseVec.push_back(optBackButton);
	
}

void OptionsUI::AddObject(std::shared_ptr<Texture> obj) {
	optionsUIBaseVec.push_back(obj);
}