#include "OptionsUI.h"
#include "GameManager.h"

OptionsUI::OptionsUI() {}

void OptionsUI::LoadOptionsUI(SDL_Renderer* renderer, GameManager* gameManager) {
	std::shared_ptr<Texture> background = std::make_shared<Texture>(renderer, GLOBAL_BACKGROUNDS_PATH + "pause.png", RELATIVE_SCREEN_WIDTH, RELATIVE_SCREEN_HEIGHT, 0, 0);
	optBackButton = std::make_shared<Button>("optionsBack", Button::UI, gameManager->GetAudioManager(), renderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 0, 0, "Back", 30);

	std::shared_ptr<Button> eraseButton(new Button("erase",
		Button::UI,
		gameManager->GetAudioManager(),
		renderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		(RELATIVE_SCREEN_WIDTH / 2 - 100), (RELATIVE_SCREEN_HEIGHT / 2) - 25,
		"Erase Data",
		25
	));

	eraseButton->OnClick = [this, gameManager]() { gameManager->DeleteAllSaves(DEFAULT_SAVE_LOCATION); };

	optionsUIBaseVec.push_back(background);
	optionsUIBaseVec.push_back(eraseButton);
	optionsUIBaseVec.push_back(optBackButton);
	
}

void OptionsUI::AddObject(std::shared_ptr<Texture> obj) {
	optionsUIBaseVec.push_back(obj);
}