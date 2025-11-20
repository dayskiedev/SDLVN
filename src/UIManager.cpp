#include <vector>
#include "UIManager.h"

UIManager::~UIManager() {
	_buttons.clear();
	
}

void UIManager::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

std::vector<std::shared_ptr<Button>> UIManager::GetUiVector() { return _buttons; }

void UIManager::AddButton(std::string btnName, std::string btnContents, int x, int y, int w, int h) {
	// should be able to set font size
	std::shared_ptr<Button> button(new Button(btnName, _renderer, DEFAULT_BUTTON_TEXTURE, w, h, x, y, btnContents, 30));
	// why do we need them to be pointers?
	_buttons.push_back(button);
}

void UIManager::AddButton(std::shared_ptr<Button> button) {
	_buttons.push_back(button);
}


void UIManager::RemoveButton(std::string btnName) {
	_buttons.clear();
}

void UIManager::RemoveButtons() {
	_buttons.clear();
}

int UIManager::GetButtonOffset() { return _btnOffset; }