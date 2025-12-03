#include <iostream>
#include <SDL.h>

#include "Texture.h"

#ifndef TEXT_H
#define TEXT_H

struct Text
{
	std::unique_ptr<Texture> textTexture = std::make_unique<Texture>();
	SDL_Color textColor; 
	std::string text = "";
	int curTextLen = 0; // change to incrementql


	// redo text to have constructor so it can be called on its own:
	// we want to set the font, size, colour
};

class Text : public Texture {
public:
	Text(std::string text, int fontSize, int x, int y, SDL_Renderer* renderer);
private:
	std::unique_ptr<Texture> textTexture = std::make_unique<Texture>();
	SDL_Color textColor;
	std::string text = "";
	int curTextLen = 0;
}

#endif
