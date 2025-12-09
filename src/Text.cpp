#include "Text.h"

Text::Text() {}

Text::Text(std::string inputText, int fontSize, TextType textType, SDL_Renderer* renderer) {
	text = inputText;

	setRenderer(renderer);
	setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize)); // setting text suze here
	curTextLen = text.length();

	loadFromRenderedText(text, textColor);
}

Text::~Text() {}


// these where casuing a stqck overflow because i renamed the render in texture.h to Render
// these where called render but also inherit from the base class, so they recusively called themselves...

void Text::Render() {
	// this will constantly load the rendered text.... might not be good....
	loadFromRenderedText(text.substr(0, curTextLen), textColor);
	Texture::Render();
}

void Text::Render(int x, int y) {
	// this will constantly load the rendered text.... might not be good....
	loadFromRenderedText(text.substr(0, curTextLen), textColor);
	Texture::Render(x, y);
}

void Text::StaticRender(int x, int y) {
	// save some resources by not constantly reloading the text (no need to... its static)
	Texture::Render(x, y);
}