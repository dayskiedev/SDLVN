#include "Game.h"

// game -> pause goes to pause state -> pause state goes to load / save state


// menu

// backboard -> text + buttons + button to close menu
// current context must be highest priority 

// must do: saving and loading selection : relies on ui
// pause: relies on ui
// settings relies on ui
// fixing game window size issues

void Game::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	// pass through the main render pointer
	// and set it to that
	gameRenderer = renderer;
	_gameManager = gameManager;

	spriteManager->setRenderer(gameRenderer);
	spriteManager->setSpriteTexPath(GLOBAL_SPRITES_PATH);

	textManager->setRenderer(gameRenderer);
	textManager->setFont(GLOBAL_FONT_PATH);

	uiManager->setRenderer(gameRenderer);

	gBackground->setRenderer(gameRenderer);

	/// REMOVE LATER
	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// NEED TO ERROR CHECK THIS

	// here is when we load values for the interpretor
	//  such as background, character sprite, etc

	// save manager needs to pass through:
	// - current interpretor line
	// - whatever the current background is
	// - whatever sprites are on screen split up into:
	//		the sprite name
	//		the sprites texture path
	//		the sprites x and y coordinate

	// game data
	auto& saveData = gameManager->GetSaveData();

	interpreter.Initialise(spriteManager, textManager, uiManager, gBackground,
		saveData.scriptLine, saveData.scriptPath, saveData.backgroundPath, saveData.sprites);

}
// run is called from main, checks for event quit
// run handles update and render as seperate methods to call

void Game::Update(SDL_Event e, double deltaTime) {
	// place logic here

	switch (currentState) {
		case RUNNING:
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					std::cout << "Pausing" << std::endl;
					currentState = PAUSED;
				}
				break;
			}

			interpreter.Run(e, deltaTime);

			for (auto b : uiManager->GetUiVector()) {
				b->Update(e);
			}
			break;
		case PAUSED:
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					std::cout << "UNPausing" << std::endl;
					currentState = RUNNING;
				}
				break;
			}
			break;
	}

}

void Game::Render() {
	// need to turn this into properly layered rendering
	// right now we can do things like hide specific layers
	// which we want to do in certain events (ie show CG background)
	SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gameRenderer);

	switch (currentState) {
		case RUNNING:
		{
			// layer -1 background
			gBackground->render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			// layer 1 character sprites
			for (auto s : spriteManager->getSpriteVector()) {
				// change render to be scaled based from settings
				s->render(s->getX(), s->getY(), s->getWidth() / 1.5, s->getHeight() / 1.5);
			}

			SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 100);
			SDL_RenderFillRect(gameRenderer, &gBlackBox);

			// this should be done in the text manager????
			// right now 

			int index = 0;
			for (auto t : textManager->getTextVector()) {
				if (t->GetCurTextLength() == 0) { continue; }
				t->Render(tOffsetX, (tOffsetY * index) + tOffsetX);
				index++;
			}

			// layer 3 buttons/ui?
			// this is where pause menu SHOULD go
			// major overhaul needed, buttons should showtext in their own render
			for (auto b : uiManager->GetUiVector()) {
				b->render();
				b->showText();
			}
			break;
		}
		case PAUSED:
			SDL_SetRenderDrawColor(gameRenderer, 22, 22, 22, 22);
			int* cxd = new int[1];
			break;
	}

	SDL_RenderPresent(gameRenderer);
}

void Game::ExitState() {	
	// make sure gamemanager is in default state
}


