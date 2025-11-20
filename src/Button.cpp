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

	//	RE USING TEXT/TEXTURE CODE (BAD)

	// SHOULD THE BUTTON BE HANDELLING THE RENDER OF BUTTON TEXT?
	textTexture = std::unique_ptr<Texture>(new Texture);

	textTexture->setRenderer(renderer);
	textTexture->setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize));
	
	textTexture->loadFromRenderedText(text, { 255,255,255 });
}

void Button::OnHover() {
	if (!entered) {
		entered = true;
		Mix_PlayChannel(2, buttonHover, 0);
	}

	setAlpha(100);
	textTexture->setAlpha(100);
}

void Button::ExitHover() {
	entered = false; 
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
	// height needs to include font size
	textTexture->render(getX() + 20, getY() + (getHeight() / 2) - 15);
}

void Button::SetButtonName(std::string btnName) {
	_btnName = btnName;
}

std::string Button::GetButtonName() { return _btnName; }