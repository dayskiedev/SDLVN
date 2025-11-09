#include <vector>
#include "UIManager.h"

void UIManager::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

std::vector<Button*> UIManager::GetUiVector() { return _buttons; }

void UIManager::AddButton(std::string btnName, std::string btnContents, int x, int y, int w, int h) {
	Button* button = new Button(btnName, _renderer, DEFAULT_BUTTON_TEXTURE, w, h, x, y, btnContents, 30);
	// why do we need them to be pointers?
	_buttons.push_back(button);
}

void UIManager::AddButton(Button* button) {
	_buttons.push_back(button);
}


void UIManager::RemoveButton(std::string btnName) {
	_buttons.clear();
}

void UIManager::RemoveButtons() {
	for (auto b : _buttons) {
		delete b;
	}
	_buttons.clear();
}

int UIManager::GetButtonOffset() { return _btnOffset; }