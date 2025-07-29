#include "TextManager.h"

TextManager::TextManager(){}
// needed construtor??

TextManager::~TextManager() {
	clearText();
}

void TextManager::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

void TextManager::setFont(std::string fontPath) {
	// seperate function for setting font path and font?
	// all fonts will be stored in the same folder in future anyway?
	_fontPath = fontPath;
	_currentFont = TTF_OpenFont(_fontPath.c_str(), _fontSize);
}

std::vector<Texture*> TextManager::getTextVector() {
	return _texts;
}

// these should not interact with event, that should be game managers job...
void TextManager::addText(std::string text) {
	// maybe add a wait for input? next time idk
	Texture* textTexture = new Texture;
	textTexture->setRenderer(_renderer);
	textTexture->setFont(_currentFont);

	//std::string rmpText = exampleCommandLine[cCount].erase(0, 6);
	textTexture->loadFromRenderedText(text, _white);
	_texts.push_back(textTexture);
}

void TextManager::clearText() {
	for (auto text : _texts) {
		delete text;
	}
	_texts.clear();
}