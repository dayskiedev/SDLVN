#include "Button.h"

Button::Button() {}

Button::Button(std::string name, ButtonType setType, SDL_Renderer* renderer, std::string texture, 
	int w, int h, int x, int y, std::string text, int fontSize) {
	setButtonName(name);
	type = setType;
	setRenderer(renderer);
	loadFromFile(texture);
	setWidth(w);
	setHeight(h);
	setX(x);
	setY(y);
	setText(text, fontSize, renderer);
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
}

Button::~Button() {
	//std::cout << "destroyed button " << this->GetButtonName() << std::endl;
}

// overloads to render text at the same time, kinda annoying...
void Button::Render() {
	Texture::Render();
	showText();
}

void Button::Render(int x, int y) {
	Texture::Render(x, y);
	showText();
}
void Button::Render(int x, int y, int w, int h) {
	Texture::Render(x, y, w, h);
	showText();
}

void Button::Update(SDL_Event e) {
	_overlapping = OverlappingCheck();

	if (_overlapping) { 
		OnHover();

		if (e.type == SDL_MOUSEBUTTONDOWN) {
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
	if (!entered) { entered = true; }

	setAlpha(100);
	// play sound here

	if (buttonText == NULL) { return; }
	buttonText->setAlpha(100);
}

void Button::ExitHover() {
	entered = false; 
	// we want this to only shoot once?
	setAlpha(255);
	//play sound here

	if (buttonText == NULL) { return;  }
	buttonText->setAlpha(255);
}

bool Button::OverlappingCheck() {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y); 

	// we need to scale the mouse coords based on resolution scale as the mouse coords
	// use window size not relative window size so windows smaller / larger than base res will have
	// more / less x y coords which mess with the buttons set x y coords leading to wrong overlaps
	mouse_x /= RESOLUTION_SCALE;
	mouse_y /= RESOLUTION_SCALE;


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