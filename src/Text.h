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

	void SetCurTextLength(int length) { curTextLen = length; }
	int GetCurTextLength() { return curTextLen; }	// what the text length CURRENTLY IS
	int GetTextLength() { return text.length();  }  // MAX text legnth
	std::string GetText() { return text; }

	void SetTextAlpha(Uint8 a);
	void SetTextColour(SDL_Color color) { textColor = color; }

	void Render(int x, int y);

	// for text whose length does not change
	void StaticRender(int x, int y);

private:
	std::unique_ptr<Texture> textTexture = std::make_unique<Texture>();
	SDL_Color textColor = { 255, 255, 255 };
	std::string text = "";
	int curTextLen = 0;
};

#endif
