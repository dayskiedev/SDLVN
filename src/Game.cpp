#include "Game.h"

// if you get the error 'The code execution cannot proceed because xxx.dll was not found.'
// check if its linked in your path variables

// TODO: 
// we want to load
// in enter state we just call the save load function
// but using default save values
// that way if we load a save, the save struct values will be changed
// so we can just call them 

//Game::Game() : interpreter(spriteManager, textManager, &uiManager, gBackground) {}

void Game::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	// pass through the main render pointer
	// and set it to that
	gameRenderer = renderer;
	_gameManager = gameManager;

	spriteManager->setRenderer(gameRenderer);
	spriteManager->setSpriteTexPath(GLOBAL_SPRITES_PATH);

	std::cout << spriteManager->getSpriteTexPath() << std::endl;

	textManager->setRenderer(gameRenderer);
	textManager->setFont(GLOBAL_FONT_PATH);

	uiManager->setRenderer(gameRenderer);

	gBackground->setRenderer(gameRenderer);

	/// REMOVE LATER
	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// NEED TO ERROR CHECK THIS

	// here is when we load values for the interpretor
	//  such as background, character sprite, etc
	
	// UI
	std::shared_ptr<Button> menuButton(new Button("quit",
		gameRenderer,
		DEFAULT_BUTTON_TEXTURE,
		250, 50,
		(SCREEN_WIDTH / 2) - 250,
		(SCREEN_HEIGHT) - 50,
		"Return to Menu",
		30
	));

	std::shared_ptr<Button> saveButton(new Button("save",
		gameRenderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		(SCREEN_WIDTH / 2),
		(SCREEN_HEIGHT)-50,
		"Save",
		30
	));


	uiManager->AddButton(menuButton);
	uiManager->AddButton(saveButton);
	menuButton->OnClick = [this]() { _gameManager->ChangeState(std::make_unique<Menu>()); };
	saveButton->OnClick = [this]() { _gameManager->SaveGame(); };

	// game data
	auto& saveData = gameManager->GetSaveData();

	interpreter.Initialise(spriteManager, textManager, uiManager, gBackground,
		saveData.scriptLine, saveData.scriptPath, saveData.backgroundPath, saveData.sprites);

}
// run is called from main, checks for event quit
// run handles update and render as seperate methods to call

void Game::Update(SDL_Event e, double deltaTime) {
	// place logic here

	interpreter.Run(e, deltaTime);

	for (auto b : uiManager->GetUiVector()) {
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
	gBackground->render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// layer 1 character sprites
	for (auto s : spriteManager->getSpriteVector()) {
		// change render to be scaled based from settings
		s->render(s->getX(), s->getY(), s->getWidth() / 1.5, s->getHeight() / 1.5);
	}

	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 100);
	SDL_RenderFillRect(gameRenderer, &gBlackBox);

	// layer 2 text
	int index = 0;
	for (auto t : textManager->getTextVector()) {
		if (t->curTextLen == 0) { continue; }
		t->textTexture->loadFromRenderedText(t->text.substr(0, t->curTextLen), t->textColor);
		t->textTexture->render(tOffsetX, (tOffsetY * index) + tOffsetX);
		index++;
	}

	// layer 3 buttons/ui?
	for (auto b : uiManager->GetUiVector()) {
		b->render(b->getX(), b->getY());
		b->showText();
	}
	SDL_RenderPresent(gameRenderer);
}

void Game::ExitState() {	

}


