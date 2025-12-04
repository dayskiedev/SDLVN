#include "PauseUI.h"

// pauseUI is its own state that contains sub states

// pauseUI.cpp will handle the UI for when the user pauses: it will
// - show the options: resume, save, load, options, return to menu
// - clicking any of these will go to the ui state and bring it up.
// - these states are seperate to the game state 
// - can show or hide the ui dending on the action

// - substates:
// [main pause] 
// - resume -> goes back to game, just hides the ui.
// - save -> switches substate to save state
// - load -> switches substate to load state
// - options -> switches substate to options state
// - return to menu -> goes back to the menu


// main functions
// loadUI -> loads all ui components at the start and hides them
// Render, handles rendering, if theyre not visable we dont render
// Update handles updates that happen, if they're not visable they should not update


// we have ui manager, why not use that?


// multiple vectors of diff ui that we want to render
// quijcsave when we go to this state

void PauseUI::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	std::cout << "We paused now";
	pauseRenderer = renderer;
}

void PauseUI::Update(SDL_Event e, double deltaTime) {

}

void PauseUI::Render() {
	SDL_SetRenderDrawColor(pauseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pauseRenderer);

	SDL_RenderPresent(pauseRenderer);
}
void PauseUI::ExitState() {

}