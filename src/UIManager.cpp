#include <vector>
#include "UIManager.h"

UIManager::UIManager() {}

UIManager::~UIManager() {
	_buttons.clear();
	_renderer = NULL;
}

void UIManager::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

SDL_Renderer* UIManager::getRenderer() { return _renderer; }

std::vector<std::shared_ptr<Button>> UIManager::GetUiVector() { return _buttons; }

void UIManager::AddButton(std::shared_ptr<Button> button) {
	_buttons.push_back(button);
}


void UIManager::RemoveButton(std::string btnName) {
	_buttons.clear();
}

void UIManager::RemoveButtons() {
	_buttons.clear();
}

void UIManager::RemoveButtonsByType(ButtonType type) {
	for (int i = _buttons.size() - 1; i >= 0; i--) {
		// we start from the back, because removing an element reduces the size of the vector
		// so if we started from the front, we would 'skip' some elements if we removed any,
		// because their position would move.
		auto btn = _buttons.at(i);
		if (btn->GetType() == type) {
			//_buttons.at(i) = _buttons.back();
			_buttons.pop_back();
		}
	}
}

int UIManager::GetButtonOffset() { return _btnOffset; }