#include <SDL.h>
#include "Texture.h"

#include <iostream>

// will mostly stick to interpretor except for main menu and screen ubttons?

#ifndef BUTTON_H
#define BUTTON_H

class Button : public Texture {
public:
	void OnClick();
	void OnHover();
	void ExitHover();
	bool OverlappingCheck();

	void SetButtonName(std::string btnName);
	std::string GetButtonName();

private:
	std::string _btnName;
	bool _overlapping;
	bool _clicked;
};

#endif