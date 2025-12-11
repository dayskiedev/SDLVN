#pragma once

#include <iostream>
#include <vector>

#include "Config.h"
#include "Texture.h"
#include "Button.h"
#include "Sprite.h"

// UI Sub-States

class OptionsUI{
public:
	OptionsUI();

	void LoadOptionsUI(SDL_Renderer* renderer);
	void AddObject(std::shared_ptr<Texture> obj);
	std::vector< std::shared_ptr<Texture>> getVector() { return optionsUIBaseVec; }

	std::shared_ptr<Button> GetBackButton() { return optBackButton; }
private:
	std::vector<std::shared_ptr<Texture>> optionsUIBaseVec;

	std::shared_ptr<Button> optBackButton;
};