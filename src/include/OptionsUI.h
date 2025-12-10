#include <iostream>
#include <vector>

#include "Config.h"
#include "Texture.h"
#include "Button.h"
#include "Sprite.h"

#ifndef OPTIONS_UI
#define OPTIONS_UI

// UI Sub-States

class OptionsUI{
public:
	OptionsUI();

	void LoadOptionsUI(SDL_Renderer* renderer);
	void AddObject(std::shared_ptr<Texture> obj);
	std::vector< std::shared_ptr<Texture>> getVector() { return optionsUIBaseVec; }
private:
	std::vector<std::shared_ptr<Texture>> optionsUIBaseVec;
};

#endif