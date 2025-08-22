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

std::vector<Text*> TextManager::getTextVector() {
	return _texts;
}

// these should not interact with event, that should be game managers job...
Text* TextManager::addText(std::string text) {
	// maybe add a wait for input? next time idk
	Text* _text = new Text;
	_text->text = text;
	_text->textTexture->setRenderer(_renderer);
	_text->textTexture->setFont(_currentFont);
	_text->textColor = _white;
	_text->curTextLen = text.length();
	//std::string rmpText = exampleCommandLine[cCount].erase(0, 6);
	//textTexture->loadFromRenderedText(text, _white);

	// change this to store structs of text, 
	// Texture* textTexture
	// int sentenceLength
	// std::string textCut = text.trim(0, sentenceLength)

	// we want to render each letter one by one based on a set speed
	// so we need a way to constantly re render EACH text

	_texts.push_back(_text);

	return _text;
}

void TextManager::clearText() {
	for (auto text : _texts) {
		delete text;
	}
	_texts.clear();
}