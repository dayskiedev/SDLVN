#include <iostream>
#include <SDL.h>

#include "Texture.h"
#include "Config.h"

#ifndef TEXT_H
#define TEXT_H
class Text : public Texture {
public:
	enum TextType
	{
		UI,
		DIALOGUE
	};

	Text(std::string text, int fontSize, TextType textType, SDL_Renderer* renderer);
	void SetTextColour(SDL_Color color) { textColor = color; }
	void SetTextLength(int length) { curTextLen = length; }
	int GetCurTextLength() { return curTextLen; }	// what the text length CURRENTLY IS
	int GetTextLength() { return text.length();  }  // MAX text legnth

	void Render(int x, int y);

private:
	std::unique_ptr<Texture> textTexture = std::make_unique<Texture>();
	SDL_Color textColor;
	std::string text = "";
	int curTextLen = 0;
};

#endif
