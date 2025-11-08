#include "Menu.h"

Texture mockLogo;
Texture background;

bool Menu::Init(SDL_Renderer* renderer) {
	if (initalised) { return true; }
	// pass through the main render pointer
	// and set it to that
	menuRenderer = renderer;
	menuUi.setRenderer(menuRenderer);

	// i should just be able to make a button constructor to create these buttons
	// so we can do things like set the functions later....
	// text should be an object i can place to.
	Button* playButton = new Button("play", 
		menuRenderer, DEFAULT_BUTTON_TEXTURE, 
		200, 100, 
		(SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) - 100, 
		"play", 
		30
	);

	Button* quitButton = new Button("quit", 
		menuRenderer, 
		DEFAULT_BUTTON_TEXTURE, 
		200, 100, 
		(SCREEN_WIDTH / 2) - 100, 
		(SCREEN_HEIGHT / 2) + 50, 
		"quit", 
		30
	);
	
	menuUi.AddButton(playButton);
	menuUi.AddButton(quitButton);
	// I NEED CONSTRUCTORRRRSSS
	mockLogo.setRenderer(menuRenderer);
	mockLogo.loadFromFile("backgrounds/logo.png");
	mockLogo.setWidth(512);
	mockLogo.setHeight(151);
	mockLogo.setX((SCREEN_WIDTH / 2) - (mockLogo.getWidth() / 2));
	mockLogo.setY(25);


	background.setRenderer(menuRenderer);
	background.loadFromFile("backgrounds/umabackground.png");
	background.setWidth(SCREEN_WIDTH);
	background.setHeight(SCREEN_HEIGHT);
	background.setX(0);
	background.setY(0);


	initalised = true;
	return true;
}

void Menu::Run(SDL_Event e, double deltaTime) {
	Update(e, deltaTime);
	Render();
}

void Menu::Update(SDL_Event e, double deltaTime) {
	for (auto b : menuUi.GetUiVector()) { b->Update(e); }
}

void Menu::Render() {
	SDL_SetRenderDrawColor(menuRenderer, 100, 100, 100, 100);
	SDL_RenderClear(menuRenderer);

	background.render();

	mockLogo.render();

	for (auto b : menuUi.GetUiVector()) { 
		b->render(); 
		b->showText();
	}

	SDL_RenderPresent(menuRenderer);
}