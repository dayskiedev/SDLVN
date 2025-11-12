#include "Button.h"

// Default Constructor 
Button::Button() {}
Button::Button(std::string name, SDL_Renderer* renderer, std::string texture, int w, int h, int x, int y, std::string text, int fontSize) {
	setRenderer(renderer);
	SetButtonName(name);
	loadFromFile(texture);
	setWidth(w);
	setHeight(h);
	setX(x);
	setY(y);
	setText(text, fontSize, renderer);
}

void Button::Update(SDL_Event e) {
	_overlapping = OverlappingCheck();

	if (_overlapping) { 
		OnHover();

		if (e.type == SDL_MOUSEBUTTONDOWN) {

			if (OnClick) { OnClick(); }
			else {
				std::cout << "ERROR: OnClick Function has not been assigned for '" << this->_btnName << "'" << std::endl;
			}

		}

	} else { ExitHover(); }
}

void Button::setText(std::string text, int fontSize, SDL_Renderer* renderer) {

	//	RE USING TEXT/TEXTURE CODE (BAD)

	// SHOULD THE BUTTON BE HANDELLING THE RENDER OF BUTTON TEXT?
	textTexture = new Texture;

	textTexture->setRenderer(renderer);
	textTexture->setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize));

	textTexture->loadFromRenderedText(text, { 255,255,255 });
}

void Button::OnHover() {
	setAlpha(100);
	textTexture->setAlpha(100);
}

void Button::ExitHover() {
	// we want this to only shoot once?
	setAlpha(255);
	textTexture->setAlpha(255);
}

bool Button::OverlappingCheck() {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	//std::cout << "mouse x " << mouse_x << " mouse y " << mouse_y << "\n";
	//std::cout << "button x " << getX() << " button y " << getY() << "\n";

	return (mouse_x >= getX() && mouse_x <= getX() + getWidth() &&
		    mouse_y >= getY() && mouse_y <= getY() + getHeight());
}

// RENDERING THE TEXT FOR THE BUTTON
void Button::showText() {
	textTexture->render(getX() + 20, getY() + (getHeight() / 2) - 20);
}

void Button::SetButtonName(std::string btnName) {
	_btnName = btnName;
}

std::string Button::GetButtonName() { return _btnName; }