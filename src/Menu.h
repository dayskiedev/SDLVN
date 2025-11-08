#include <SDL.h>

#include <iostream>

#include "Config.h"
#include "UIManager.h"

#ifndef MENU_H
#define MENU_H

class Menu {
public:
	bool Init(SDL_Renderer* renderer);
	void Run(SDL_Event e, double deltaTime);
	void Update(SDL_Event e, double deltaTime);
	void Render();
private:
	bool initalised = false;

	// window renderer
	SDL_Renderer* menuRenderer = NULL;
	UIManager menuUi;
};

#endif