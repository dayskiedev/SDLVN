#pragma once

#include <iostream>
#include <SDL.h>

#include "Texture.h"
#include "Config.h"

class Text : public Texture {
public:
	// may need to rework this to include a texture?
	enum TextType
	{
		UI,
		DIALOGUE
	};

	Text();
	Text(std::string text, int fontSize, TextType textType, SDL_Renderer* renderer);
	~Text();

	void SetCurTextLength(int length) { curTextLen = length; }
	int GetCurTextLength() { return curTextLen; }	// what the text length CURRENTLY IS
	size_t GetTextLength() { return text.length();  }  // MAX text legnth
	std::string GetText() { return text; }

	// like this stuff can be done in the texture?
	void SetTextAlpha(int a);
	void SetTextColour(SDL_Color color) { textColor = color; }

	void Render();
	void Render(int x, int y);

	void Update() {}

	// for text whose length does not change
	void StaticRender(int x, int y);

private:
	SDL_Color textColor = { 255, 255, 255 };
	std::string text = "";
	int curTextLen = 0;
};