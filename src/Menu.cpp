#include "Menu.h"

// unique pointer assigns ownership
std::unique_ptr<Texture> mockLogo;
std::unique_ptr<Texture> background;

void Menu::EnterState(SDL_Renderer* renderer) {
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

	// these load the textures but they do not get shown?
	mockLogo = std::make_unique<Texture>(menuRenderer, "backgrounds/logo.png", 512, 151, (SCREEN_WIDTH / 2) - (512 / 2), 25);
	background = std::make_unique<Texture>(menuRenderer, "backgrounds/umabackground.png", SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
}

void Menu::Run(SDL_Event e, double deltaTime) {
	// have this be its own loop that can be exited?
	// that way init can run just once inside the main loop?
	
	// enter state calls the init,
	// exit state calls destructors etc

	// question is how do we go back to another state after switching, call the function again?
	// in that case we already have our base case, the quit check
	// this function should return the state to switch to?s

	Update(e, deltaTime);
	Render();

}

void Menu::Update(SDL_Event e, double deltaTime) {
	for (auto b : menuUi.GetUiVector()) { b->Update(e); }
}

void Menu::Render() {
	SDL_SetRenderDrawColor(menuRenderer, 100, 100, 100, 100);
	SDL_RenderClear(menuRenderer);

	background->render();

	mockLogo->render();

	for (auto b : menuUi.GetUiVector()) { 
		b->render(); 
		b->showText();
	}

	SDL_RenderPresent(menuRenderer);
}