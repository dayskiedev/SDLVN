#include "Game.h"
#include "GameManager.h"
#include "UIManager.h"

// settings relies on ui
// fixing game window size issues

void Game::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	gameRenderer = renderer;
	_gameManager = gameManager;
	_gameManager->SetSaveReferences(interpreter, spriteManager, gBackground);

	spriteManager->setRenderer(gameRenderer);
	spriteManager->setSpriteTexPath(GLOBAL_SPRITES_PATH);

	textManager->setRenderer(gameRenderer);
	textManager->setFont(GLOBAL_FONT_PATH);

	uiManager->setRenderer(gameRenderer);

	gBackground->setRenderer(gameRenderer);

	/// setup ui stuff, including initialisng the pause menu options (that should probably be a seperate file?
	gBlackBox = { 0,0, RELATIVE_SCREEN_WIDTH, RELATIVE_SCREEN_HEIGHT };

	//should this be its own function / file?
	uma = std::make_shared<Sprite>("uma", GLOBAL_SPRITES_PATH + "saveicon.png", RELATIVE_SCREEN_WIDTH - 800, (RELATIVE_SCREEN_HEIGHT / 2) - 300, 800, 800, 1.0, gameRenderer);
	std::shared_ptr<Button> resumeButton(new Button("resume", Button::UI, gameManager->GetAudioManager(), gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 150, 150,"Resume", 30));
	std::shared_ptr<Button> optButton(new Button("options", Button::UI, gameManager->GetAudioManager(), gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 110, 250, "Options", 30));
	std::shared_ptr<Button> saveButton(new Button("save", Button::UI, gameManager->GetAudioManager(), gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 75, 350, "Save", 30));
	std::shared_ptr<Button> loadButton(new Button("load", Button::UI, gameManager->GetAudioManager(), gameRenderer, DEFAULT_BUTTON_TEXTURE, 200, 50, 110, 450, "Load", 30));
	std::shared_ptr<Button> menuButton(new Button("quit", Button::UI, gameManager->GetAudioManager(), gameRenderer, DEFAULT_BUTTON_TEXTURE, 250, 50, 150, 550, "Return to Menu", 30));

	PauseMainMenuUI.push_back(resumeButton);
	PauseMainMenuUI.push_back(optButton);
	PauseMainMenuUI.push_back(saveButton);
	PauseMainMenuUI.push_back(loadButton);
	PauseMainMenuUI.push_back(menuButton);
	resumeButton->OnClick = [this]() { currentState = RUNNING; };
	optButton->OnClick = [this]() { pauseState = OPTIONS_MENU; };
	saveButton->OnClick = [this]() { 
		// get save load vuttons here?
		// then set the onclicks to this function?, with extra arg of
		// the button name?
		saveLoadUI->UpdateFileButtons(SaveLoadUI::SAVE);
		pauseState = SAVE_MENU;

		//_gameManager->SaveGame(interpreter, spriteManager, gBackground); 
	};
	loadButton->OnClick = [this]() { 
		saveLoadUI->UpdateFileButtons(SaveLoadUI::LOAD);
		pauseState = LOAD_MENU;
	};
	menuButton->OnClick = [this]() { _gameManager->RequestState(std::make_unique<Menu>()); };

	// should be a constructor
	std::shared_ptr<Text> pauseText = std::make_unique<Text>("PAUSEDPAUSEDPAUSEDPAUSEDPAUSEDPAUSEDPAUSEDPAUSED", 120, Text::UI, gameRenderer);
	pauseText->setX((RELATIVE_SCREEN_WIDTH / 2) - pauseText->getWidth() / 2);
	PauseMainMenuUI.push_back(pauseText);


	// Options UI
	optionsUI->LoadOptionsUI(gameRenderer, gameManager);
	optionsUI->GetBackButton()->OnClick = [this]() { pauseState = PAUSED_MENU; };

	saveLoadUI->LoadSaveLoadUI(gameRenderer, gameManager);
	saveLoadUI->GetBackButton()->OnClick = [this]() { pauseState = PAUSED_MENU; };

	// game data
	auto& saveData = gameManager->GetSaveData();
	// why dont we just push save data through here?
	interpreter->Initialise(spriteManager, textManager, uiManager, gameManager->GetAudioManager(), gBackground,
		saveData.scriptLine, saveData.scriptPath, saveData.backgroundPath, saveData.sprites);
}
// run is called from main, checks for event quit
// run handles update and render as seperate methods to call

void Game::Update(SDL_Event e, double deltaTime) {
	// game logic updates here

	switch (currentState) {
		case RUNNING:
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					currentState = PAUSED;
				}
				break;
			}

			// ALL MAIN GAME LOGIC RUNS THROUGH HERE BTW
			interpreter->Run(e, deltaTime);

			for (auto b : uiManager->GetUiVector()) {
				b->Update(e);
			}
			break;

		case PAUSED:
			switch (pauseState) {
				case PAUSED_MENU:
					for (auto& obj : PauseMainMenuUI) { obj->Update(e); }
					break;
				case SAVE_MENU:
					for (auto& obj : saveLoadUI->getVector()) { obj->Update(e); }
					break;
				case LOAD_MENU:
					for (auto& obj : saveLoadUI->getVector()) { obj->Update(e); }
					break;
				case OPTIONS_MENU:
					for (auto& obj : optionsUI->getVector()) { obj->Update(e); }
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
			gBackground->Render(0, 0, RELATIVE_SCREEN_WIDTH, RELATIVE_SCREEN_HEIGHT);

			// layer 1 character sprites
			for (auto s : spriteManager->getSpriteVector()) {
				// change render to be scaled based from settings
				s->Render();
				//s->Render();
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

			switch (pauseState)
			{
			case PAUSED_MENU:
				// keep rendering background
				gBackground->Render(0, 0, RELATIVE_SCREEN_WIDTH, RELATIVE_SCREEN_HEIGHT);

				// dim background slightly
				SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 100);
				SDL_RenderFillRect(gameRenderer, &gBlackBox);

				// for some reason we need to get the x and y values of the object,
				// even though the base render uses the same values?
				for (auto& b : PauseMainMenuUI) {
					b->Render();
				}

				uma->Render();
				break;
			case SAVE_MENU:
				for (auto& obj : saveLoadUI->getVector()) {
					obj->Render();
				}
				break;
			case LOAD_MENU:
				for (auto& obj : saveLoadUI->getVector()) {
					obj->Render();
				}
				break;
			case OPTIONS_MENU:
				for (auto& obj : optionsUI->getVector()) {
					obj->Render();
				}
				break;
			}
			break;
	}

	SDL_RenderPresent(gameRenderer);
}

void Game::ExitState() {	
	// exit code here
	_gameManager->GetAudioManager()->StopSong();
	PauseMainMenuUI.clear();
}


