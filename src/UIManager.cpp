#include <vector>
#include "UIManager.h"

void UIManager::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

std::vector<Button*> UIManager::GetUiVector() { return _buttons; }


void UIManager::AddButton(std::string btnName, std::string btnContents, int x, int y, int w, int h) {
	Button* button = new Button;
	button->setRenderer(_renderer);
	button->SetButtonName(btnName);
	button->loadFromFile(DEFAULT_BUTTON_TEXTURE);

	button->setX(x);
	button->setY(y);

	button->setWidth(w);
	button->setHeight(h);

	button->setText(btnContents, 30, _renderer);
	// buttons we want to render text, and then the button
	// pushback adds element at the end of vector, so we add button and then text
	// so the button is rendered then the text'

	_buttons.push_back(button);
}

void UIManager::RemoveButton(std::string btnName) {
	_buttons.clear();
}

void UIManager::RemoveButtons() {
	// NEEDS TO BE MORE SPECIFIC TO CHOICE BUTTONS LATER (SOME SORT OF TAG SYSTEM?)
	_buttons.clear();
}

int UIManager::GetButtonOffset() { return _btnOffset; }