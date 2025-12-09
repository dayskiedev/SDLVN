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


	// THIS WILL BE MOVE TO THE PAUSE UI CPP FILE TO INITIALISE THERE INSTEAD? IDK

	// also by god stop with the magic numbers...
	uma = std::make_shared<Sprite>("uma", GLOBAL_SPRITES_PATH + "saveicon.png", SCREEN_WIDTH - 800, (SCREEN_HEIGHT / 2) - 300, 800, 800, gameRenderer);
	std::shared_ptr<Button> resumeButton(new Button("resume", Button::UI, gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 150, 150,"Resume", 30));
	std::shared_ptr<Button> optButton(new Button("options", Button::UI, gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 110, 250, "Options", 30));
	std::shared_ptr<Button> saveButton(new Button("save", Button::UI, gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 75, 350, "Save", 30));
	std::shared_ptr<Button> loadButton(new Button("load", Button::UI, gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 110, 450, "Load", 30));
	std::shared_ptr<Button> menuButton(new Button("quit", Button::UI, gameRenderer, DEFAULT_BUTTON_TEXTURE, 250, 50, 150, 550, "Return to Menu", 30));

	PauseMainMenuUI.push_back(resumeButton);
	PauseMainMenuUI.push_back(optButton);
	PauseMainMenuUI.push_back(saveButton);
	PauseMainMenuUI.push_back(loadButton);
	PauseMainMenuUI.push_back(menuButton);
	resumeButton->OnClick = [this]() { currentState = RUNNING; };
	optButton->OnClick = [this]() { std::cout << "show options menu" << std::endl; };
	saveButton->OnClick = [this]() { _gameManager->SaveGame(interpreter, spriteManager, gBackground); };
	loadButton->OnClick = [this]() { std::cout << "Show saves to load here" << std::endl; };
	menuButton->OnClick = [this]() { _gameManager->RequestState(std::make_unique<Menu>()); };

	// should be a constructor
	std::shared_ptr<Text> pauseText = std::make_unique<Text>("PAUSEDPAUSEDPAUSEDPAUSEDPAUSEDPAUSEDPAUSEDPAUSED", 120, Text::UI, gameRenderer);
	pauseText->setX((SCREEN_WIDTH / 2) - pauseText->getWidth() / 2);
	PauseMainMenuUI.push_back(pauseText);

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

			// ALL MAIN GAME LOGIC RUNS THROUGH HERE BTW
			interpreter.Run(e, deltaTime);

			for (auto b : uiManager->GetUiVector()) {
				b->Update(e);
			}
			break;

		case PAUSED:
			switch (pauseState) {
				case PAUSED_MENU:
					for (auto& b : PauseMainMenuUI) {
						b->Update(e); 
					}
					break;
				case SAVE_MENU:
					break;
				case LOAD_MENU:
					break;
				case OPTIONS_MENU:
					break;
			}
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
			gBackground->Render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			// layer 1 character sprites
			for (auto s : spriteManager->getSpriteVector()) {
				// change render to be scaled based from settings
				s->Render(s->getX(), s->getY(), s->getWidth() / 1.5, s->getHeight() / 1.5);
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
				b->Render();
			}
			break;
		}
		case PAUSED:
			// keep rendering background
			gBackground->Render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			// dim background slightly
			SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 100);
			SDL_RenderFillRect(gameRenderer, &gBlackBox);

			// for some reason we need to get the x and y values of the object,
			// even though the base render uses the same values?
			for (auto b : PauseMainMenuUI) {
				b->Render();
			}

			uma->Render();
			break;
	}

	SDL_RenderPresent(gameRenderer);
}

void Game::ExitState() {	
	// exit code here
}


