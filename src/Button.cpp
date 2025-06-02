#include "Button.h"


void Button::OnClick() {
	std::cout << "click\n";
	// needs to be a broadcast event so we know what button was clicked?
	// otherwse we only have this hardcoded click, making it a signal to listen out for
	// lets us define custom behaviour per button?
}

void Button::OnHover() {
	setAlpha(100);
}

void Button::ExitHover() {
	// we want this to only shoot once?
	setAlpha(255);
}

bool Button::OverlappingCheck() {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	//std::cout << "mouse x " << mouse_x << " mouse y " << mouse_y << "\n";
	//std::cout << "button x " << getX() << " button y " << getY() << "\n";

	if (mouse_x >= getX() && mouse_x <= getX() + getWidth() && 
		mouse_y >= getY() && mouse_y <= getY() + getHeight()) {
		OnHover();
		return true;
	}
	ExitHover();
	return false;

}