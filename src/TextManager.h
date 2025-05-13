#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Texture.h"

#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

class TextManager : public Texture {
public:
	TextManager();
	~TextManager();

	void setRender(SDL_Renderer* renderer);
	void setFont(std::string fontPath);

	void addText(std::string text);
	void clearText();

	std::vector<Texture*> getTextVector();
private:
	std::vector<Texture*> _texts;
	SDL_Renderer* _renderer = NULL;

	std::string _fontPath;
	TTF_Font* _currentFont = NULL;
	int _fontSize = 28;

	// should these be in their own file?
	SDL_Color _white = { 255,255,255 };
	SDL_Color _black = { 0,0,0 };
};

#endif 
