#include "Game.h"

// if you get the error 'The code execution cannot proceed because xxx.dll was not found.'
// check if its linked in your path variables

// TODO: 

// ensure every system can properly load before we run the game, if we run into errors
// we want to exit early

void Game::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	// pass through the main render pointer
	// and set it to that
	gameRenderer = renderer;

	// LOAD GLOBALS (there has to be a better way to do this?
	spriteManager.setRenderer(gameRenderer);
	spriteManager.setSpriteTexPath(GLOBAL_SPRITES_PATH);

	textManager.setRenderer(gameRenderer);
	textManager.setFont(GLOBAL_FONT_PATH);

	uiManager.setRenderer(gameRenderer);

	gBackground.setRenderer(gameRenderer);

	/// REMOVE LATER
	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// NEED TO ERROR CHECK THIS
	interpreter.OpenScript(GLOBAL_SCRIPTS_PATH + script_name);
}
// run is called from main, checks for event quit
// run handles update and render as seperate methods to call

void Game::Update(SDL_Event e, double deltaTime) {
	// place logic here

	interpreter.Run(e, deltaTime, spriteManager, textManager, uiManager, gBackground);

	for (auto b : uiManager.GetUiVector()) {
		b->Update(e);
	}
}

void Game::Render() {
	// need to turn this into properly layered rendering
	// right now we can do things like hide specific layers
	// which we want to do in certain events (ie show CG background)
	SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gameRenderer);

	// layer -1 background
	gBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// layer 1 character sprites
	for (auto s : spriteManager.getSpriteVector()) {
		// change render to be scaled based from settings
		s->render(s->getX(), s->getY(), s->getWidth() / 1.5, s->getHeight() / 1.5);
	}

	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 100);
	SDL_RenderFillRect(gameRenderer, &gBlackBox);

	// layer 2 text
	int index = 0;
	for (auto t : textManager.getTextVector()) {
		if (t->curTextLen == 0) { continue; }
		t->textTexture->loadFromRenderedText(t->text.substr(0, t->curTextLen), t->textColor);
		t->textTexture->render(tOffsetX, (tOffsetY * index) + tOffsetX);
		index++;
	}

	// layer 3 buttons/ui?
	for (auto b : uiManager.GetUiVector()) {
		b->render(b->getX(), b->getY());
		b->showText();
	}
	SDL_RenderPresent(gameRenderer);
}

void Game::ExitState() {
	// placeholder
}


