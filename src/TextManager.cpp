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

std::vector<std::shared_ptr<Text>> TextManager::getTextVector() {
	return _texts;
}

std::shared_ptr<Text> TextManager::addText(std::string text) {
	// needs constructor
	std::shared_ptr<Text> _text(new Text(text, _fontSize, Text::DIALOGUE, _renderer));
	_text->SetCurTextLength(0); // since we want this to update we set the text length to 0
	_texts.push_back(_text);

	return _text;
}

void TextManager::clearText() {
	// text should be auto deleted by pointer
	_texts.clear();
}