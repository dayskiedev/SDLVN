#include "Text.h"

Text::Text(std::string inputText, int fontSize, TextType textType, SDL_Renderer* renderer) {
	text = inputText;

	textTexture->setRenderer(renderer);
	textTexture->setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize)); // setting text suze here
	curTextLen = text.length();

	textTexture->loadFromRenderedText(text, textColor);
}

void Text::SetTextAlpha(Uint8 a) {
	textTexture->setAlpha(a);
}

void Text::Render(int x, int y) {
	// this will constantly load the rendered text.... might not be good....
	textTexture->loadFromRenderedText(text.substr(0, curTextLen), textColor);
	textTexture->render(x, y);
}

void Text::StaticRender(int x, int y) {
	// save some resources by not constantly reloading the text (no need to... its static)
	textTexture->render(x, y);
}