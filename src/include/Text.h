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
	Text(std::string text, int fontSize, int x, int y, TextType textType, SDL_Renderer* renderer);
	~Text();


	void SetText(std::string t);
	std::string GetText() { return text; }

	void SetCurTextLength(int length) { curTextLen = length; }
	int GetCurTextLength() { return curTextLen; }	// what the text length CURRENTLY IS
	size_t GetTextLength() { return text.length();  }  // MAX text legnth

	// like this stuff can be done in the texture?
	void SetTextColour(SDL_Color color) { textColor = color; }

	void Render();
	void Render(double x, double y);

	void Update() {}

	// for text whose length does not change
	void StaticRender(double x, double y);

private:
	SDL_Color textColor = { 255, 255, 255 };
	std::string text = "";
	int curTextLen = 0;
};