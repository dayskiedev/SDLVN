#include "Button.h"

// Default Constructor 
Button::Button() {}
Button::Button(std::string name, ButtonType setType, SDL_Renderer* renderer, std::string texture, int w, int h, int x, int y, std::string text, int fontSize) {
	setButtonName(name);
	type = setType;
	setRenderer(renderer);
	loadFromFile(texture);
	setWidth(w);
	setHeight(h);
	setX(x);
	setY(y);
	setText(text, fontSize, renderer);

	// set button hover sound
	// should be done in audiomanager?
	buttonHover = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_hover.wav").c_str());
	buttonClick = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_click.wav").c_str());
	if (buttonClick == NULL) { std::cout << "erorr]\n"; }
}

Button::Button(std::string name, ButtonType setType, SDL_Renderer* renderer, std::string texture, int w, int h, int x, int y) {
	setButtonName(name);
	type = setType;
	setRenderer(renderer);
	loadFromFile(texture);
	setWidth(w);
	setHeight(h);
	setX(x);
	setY(y);
	// set button hover sound
	// should be done in audiomanager?
	buttonHover = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_hover.wav").c_str());
	buttonClick = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_click.wav").c_str());
	if (buttonClick == NULL) { std::cout << "erorr]\n"; }
}

Button::~Button() {
	// button specifc destructors (ie sounds)
	Mix_FreeChunk(buttonHover);
	buttonHover = NULL;
	Mix_FreeChunk(buttonClick);
	buttonClick = NULL;
	//std::cout << "destroyed button " << this->GetButtonName() << std::endl;
}

void Button::Update(SDL_Event e) {
	_overlapping = OverlappingCheck();

	if (_overlapping) { 
		OnHover();

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			Mix_PlayChannel(2, buttonClick, 0);
			if (OnClick) { 
				OnClick(); 
			}
			else {
				std::cout << "ERROR: OnClick Function has not been assigned for '" << this->_btnName << "'" << std::endl;
			}

		}

	} else { ExitHover(); }
}

void Button::setText(std::string text, int fontSize, SDL_Renderer* renderer) {
	// Text is now a simple object that is constrcuted the same way in multiple spaces
	buttonText = std::unique_ptr<Text>(new Text(text, fontSize, Text::UI, renderer));
}

void Button::OnHover() {
	if (!entered) {
		entered = true;
		Mix_PlayChannel(2, buttonHover, 0);
	}

	setAlpha(100);

	if (buttonText == NULL) { return; }
	buttonText->SetTextAlpha(100);
}

void Button::ExitHover() {
	entered = false; 
	// we want this to only shoot once?
	setAlpha(255);

	if (buttonText == NULL) { return;  }
	buttonText->SetTextAlpha(255);
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
	// height needs to include font size
	if (buttonText == NULL) { return; }

	//HARD CODED VALUES ARE BAD!!!
	// using static render as button text should not change
	buttonText->StaticRender(getX() + 20, getY() + (getHeight() / 2) - 15);
}

void Button::setButtonName(std::string btnName) {
	_btnName = btnName;
}

std::string Button::GetButtonName() { return _btnName; }

Button::ButtonType Button::GetType() { return type; }