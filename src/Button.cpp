#include "Button.h"


void Button::OnClick() {
	//std::cout << "hi my name is " << _btnName << "\n";
	// 
	OnClickPtr();
	// needs to be a broadcast event so we know what button was clicked?
	// otherwse we only have this hardcoded click, making it a signal to listen out for
	// lets us define custom behaviour per button?

	// create a button selection type
		
	// rather than having each button be a defined class, they can send out an event signal?
}

void Button::Update(SDL_Event e) {
	_overlapping = OverlappingCheck();

	if (_overlapping) { 
		OnHover();

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			OnClick();
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

	if (mouse_x >= getX() && mouse_x <= getX() + getWidth() && 
		mouse_y >= getY() && mouse_y <= getY() + getHeight()) {
		return true;
	}

	return false;

}

// RENDERING THE TEXT FOR THE BUTTON
void Button::showText() {
	textTexture->render(getX() + 20, getY() + (getHeight() / 2) - 20);
}

void Button::SetButtonName(std::string btnName) {
	_btnName = btnName;
}

std::string Button::GetButtonName() { return _btnName; }