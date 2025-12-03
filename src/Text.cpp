#include "Text.h"

Text::Text(std::string inputText, int fontSize, TextType textType, SDL_Renderer* renderer) {
	text = inputText;

	textTexture->setRenderer(renderer);
	textTexture->setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize)); // setting text suze here
	curTextLen = text.length();
}

void Text::Render(int x, int y) {
	// this will constantly load the rendered text.... might not be good....
	textTexture->loadFromRenderedText(text.substr(0, curTextLen), textColor);
	textTexture->render(x, y);
}