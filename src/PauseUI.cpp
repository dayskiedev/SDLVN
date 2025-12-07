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



// NOTE FOR SAVING AND LOADNIG
// HAVE SOME SORT OF BASE CLASS FILE THAT THEY INHERET FROM
// THE INITIALISATION WILL BE EVERYTHING UI RELATED HOWEVER
// THE BACK BUTTON WILL BE DIFFERENT DEPENDING ON WHERE IT IS MADE
// SAME WHEN CLICKING ON SAVES
// SO IN THIS CASE ONLY DEFINE THE UI, LEAVE BUTTON CLICKS BLANK FOR BASE CLASS



// multiple vectors of diff ui that we want to render
// quijcsave when we go to this state

void PauseUI::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	std::cout << "We paused now";
	pauseRenderer = renderer;
	_gameManager = gameManager;

	// create all vector renders and set initial enum
	// make some sort of ui definition template?

	std::shared_ptr<Button> returnTestButton(new Button("return", Button::UI, pauseRenderer, DEFAULT_BUTTON_TEXTURE, 200, 200, 0, 0, "resume", 32));
	returnTestButton->OnClick = [this]() {_gameManager->ChangeState(std::make_unique<Game>()); };
	testUI.push_back(returnTestButton);
}

void PauseUI::Update(SDL_Event e, double deltaTime) {
	for (auto b : testUI) {
		b->Update(e);
	}
}

void PauseUI::Render() {	
	SDL_SetRenderDrawColor(pauseRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pauseRenderer);

	for (auto b : testUI) {
		b->render();
		b->showText();
	}

	SDL_RenderPresent(pauseRenderer);
}
void PauseUI::ExitState() {

}