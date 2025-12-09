#include "Text.h"

Text::Text() {}

Text::Text(std::string inputText, int fontSize, TextType textType, SDL_Renderer* renderer) {
	text = inputText;

	textTexture->setRenderer(renderer);
	textTexture->setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize)); // setting text suze here
	curTextLen = text.length();

	textTexture->loadFromRenderedText(text, textColor);
}

Text::~Text() {}

void Text::SetTextAlpha(int a) {
	textTexture->setAlpha(a);
}

void Text::Render() {
	// this will constantly load the rendered text.... might not be good....
	textTexture->loadFromRenderedText(text.substr(0, curTextLen), textColor);
	textTexture->Render();
}

void Text::Render(int x, int y) {
	// this will constantly load the rendered text.... might not be good....
	textTexture->loadFromRenderedText(text.substr(0, curTextLen), textColor);
	textTexture->Render(x, y);
}

void Text::StaticRender(int x, int y) {
	// save some resources by not constantly reloading the text (no need to... its static)
	textTexture->Render(x, y);
}