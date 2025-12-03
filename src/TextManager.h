#include <iostream>
#include <vector>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Texture.h"
#include "Text.h"

#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

class TextManager : public Texture {
public:
	TextManager();
	~TextManager();

	void setRenderer(SDL_Renderer* renderer);
	void setFont(std::string fontPath);

	std::shared_ptr<Text> addText(std::string text);
	void clearText();

	std::vector<std::shared_ptr<Text>> getTextVector();
private:
	std::vector<std::shared_ptr<Text>> _texts;
	SDL_Renderer* _renderer = NULL;

	std::string _fontPath;

	// we must keep fonts as pointers sdl definition?
	TTF_Font* _currentFont = NULL;
	int _fontSize = 32;

	// should these be in their own file?
	SDL_Color _white = { 255,255,255 };
	SDL_Color _black = { 0,0,0 };
};

#endif 
