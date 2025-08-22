#include <iostream>
#include <SDL.h>

#include "Texture.h"

#ifndef DIALOGUELINE_H
#define DIALOGUELINE_H

struct Text
{
	Texture* textTexture = new Texture;
	SDL_Color textColor;
	std::string text = "";
	int curTextLen = 0; // change to incrementql
};

#endif
