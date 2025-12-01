#include <SDL.h>
#include <SDL_mixer.h>
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
	enum ButtonType
	{
		CHOICE,
		REPLY,
		UI
	};

	Button();
	Button(std::string name, ButtonType type, SDL_Renderer* renderer, std::string texture, int w, int h, int x, int y, std::string text, int fontSize);

	// button without text
	Button(std::string name, SDL_Renderer* renderer, std::string texture, int w, int h, int x, int y);

	~Button();
	
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
	ButtonType type;
	bool _overlapping;
	bool _clicked;
	bool entered;
	bool hasText;

	std::unique_ptr<Texture> textTexture = NULL;
	TTF_Font* _font = NULL;
	Mix_Chunk* buttonHover;
	Mix_Chunk* buttonClick;
};

#endif