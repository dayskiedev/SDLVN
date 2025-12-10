#include "OptionsUI.h"

OptionsUI::OptionsUI() {}

void OptionsUI::LoadOptionsUI(SDL_Renderer* renderer) {
	std::shared_ptr<Texture> background = std::make_shared<Texture>(renderer, GLOBAL_BACKGROUNDS_PATH + "pause.png", SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	optionsUIBaseVec.push_back(background);
}

void OptionsUI::AddObject(std::shared_ptr<Texture> obj) {
	optionsUIBaseVec.push_back(obj);
}