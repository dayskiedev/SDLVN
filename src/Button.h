#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <functional>

#include "Texture.h"
#include "Config.h"

// will mostly stick to interpretor except for main menu and screen ubttons?

#ifndef BUTTON_H
#define BUTTON_H

class Button : public Texture {
public:
	//Button();
	//Button(std::string name, SDL_Renderer renderer, std::string texture, int x, int y, int w, int h, std::string text, int fontSize);
	//
	//void OnClick();
	std::function<void()> OnClick;
	void OnHover();	
	void ExitHover();
	bool OverlappingCheck();

	void setText(std::string text, int fontSize, SDL_Renderer* renderer);
	void showText();

	void Update(SDL_Event e);


	void SetButtonName(std::string btnName);
	std::string GetButtonName();

private:
	std::string _btnName;
	bool _overlapping;
	bool _clicked;

	Texture* textTexture = NULL;
};

#endif