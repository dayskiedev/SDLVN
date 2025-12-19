#include "Text.h"

Text::Text() {}

Text::Text(std::string inputText, int fontSize, TextType textType, SDL_Renderer* renderer) {
	text = inputText;

	setRenderer(renderer);
	setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize)); // setting text suze here
	curTextLen = text.length();

	loadFromRenderedText(text, textColor);
}

Text::Text(std::string inputText, int fontSize, int x, int y, TextType textType, SDL_Renderer* renderer) {
	text = inputText;

	setRenderer(renderer);
	setFont(TTF_OpenFont(GLOBAL_FONT_PATH.c_str(), fontSize)); // setting text suze here
	curTextLen = text.length();

	loadFromRenderedText(text, textColor);
	setX(x);
	setY(y);
}

Text::~Text() {}

void Text::SetText(std::string t) {
	text = t;
	curTextLen = text.length();
	loadFromRenderedText(text, textColor);

	// have some sort of text anchor enum to ensure text stays in correct position
	// depending on what anchor we have (ex left anchor, centre anchor etc)
	// right now we default to having text centre at its x/y
	setX((RELATIVE_SCREEN_WIDTH / 2) - (getWidth() / 2));
}

// these where casuing a stqck overflow because i renamed the render in texture.h to Render
// these where called render but also inherit from the base class, so they recusively called themselves...
void Text::Render() {
	// this will constantly load the rendered text.... might not be good....
	loadFromRenderedText(text.substr(0, curTextLen), textColor);
	Texture::Render();
}

void Text::Render(double x, double y) {
	// this will constantly load the rendered text.... might not be good....
	loadFromRenderedText(text.substr(0, curTextLen), textColor);
	Texture::Render(x, y);
}

void Text::StaticRender(double x, double y) {
	// save some resources by not constantly reloading the text (no need to... its static)
	Texture::Render(x, y);
}