#include "Text.h"

Text::Text(std::string text, int fontSize, TextType textType, SDL_Renderer* renderer) {
	textTexture->setRenderer(renderer);
	textTexture->setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize)); // setting text suze here

	curTextLen = text.length();

	textTexture->loadFromRenderedText(text, { 255, 255, 255 });
}

void Text::Render(int x, int y) {
	// render text here instead of in game
	textTexture->loadFromRenderedText(text.substr(0, curTextLen), textColor);
	textTexture->render(x, y);
}