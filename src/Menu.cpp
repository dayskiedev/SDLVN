#include "Menu.h"

// unique pointer assigns ownership
std::unique_ptr<Texture> background;	

void Menu::EnterState(SDL_Renderer* renderer, GameManager* gameManager) {
	// pass through the main render pointer
	// and set it to that
	_gameManager = gameManager;
	menuRenderer = renderer;
	menuUi = std::make_unique<UIManager>();
	menuUi->setRenderer(menuRenderer);

	// these load the textures but they do not get shown?
	background = std::make_unique<Texture>( menuRenderer, GLOBAL_BACKGROUNDS_PATH + "/umabackground2.png",
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0, 0
	);

	std::shared_ptr<Button> playButton(new Button("new", Button::UI, menuRenderer, DEFAULT_BUTTON_TEXTURE, 
		200, 50,					// width height
		(SCREEN_WIDTH / 2) - 100,	// x
		(SCREEN_HEIGHT / 2) - 50,   // y
		"New Game",					// Button contents
		30							// Font size for button contents
	));

	std::shared_ptr<Button> contButton(new Button("load", Button::UI, menuRenderer, DEFAULT_BUTTON_TEXTURE,
		200,50,
		(SCREEN_WIDTH / 2) - 100,
		(SCREEN_HEIGHT / 2), 
		"Load Save",
		30
	));

	std::shared_ptr<Button> optButton(new Button("options", Button::UI,menuRenderer,DEFAULT_BUTTON_TEXTURE,
		200, 50,
		(SCREEN_WIDTH / 2) - 100,
		(SCREEN_HEIGHT / 2) + 50,
		"Options",
		30
	));

	std::shared_ptr<Button> quitButton(new Button("quit", Button::UI, menuRenderer, DEFAULT_BUTTON_TEXTURE, 
		200, 50, 
		(SCREEN_WIDTH / 2) - 100, 
		(SCREEN_HEIGHT / 2) + 100, 
		"Exit", 
		30
	));

	// define on click actions for buttons
	playButton->OnClick = [this]() { 
		_gameManager->SetDefaultGameState();
		_gameManager->ChangeState(std::make_unique<Game>()); 
	};
	contButton->OnClick = [this]() { _gameManager->ChangeState(std::make_unique<Load>()); };
	optButton->OnClick = [this]() { _gameManager->ChangeState(std::make_unique<Options>()); };
	quitButton->OnClick = [this]() { _gameManager->running = false; };
	
	menuUi->AddButton(playButton);
	menuUi->AddButton(contButton);
	menuUi->AddButton(optButton);
	menuUi->AddButton(quitButton);

	title = std::make_unique<Text>("SDLVN", 120, Text::UI, menuRenderer);
	version = std::make_unique<Text>("v0.1.4", 30, Text::UI, menuRenderer);
}

void Menu::Update(SDL_Event e, double deltaTime) {
	for (auto b : menuUi->GetUiVector()) { b->Update(e); }
}

void Menu::Render() {
	SDL_SetRenderDrawColor(menuRenderer, 100, 100, 100, 100);
	SDL_RenderClear(menuRenderer);

	background->Render();

	for (auto b : menuUi->GetUiVector()) { 
		b->Render(); 
		// why is this seperate lol?
		b->showText();
	}

	title->StaticRender(SCREEN_WIDTH / 2 - (title->GetTextWidth() / 2), 100);
	version->StaticRender(15, SCREEN_HEIGHT - version->GetTextHeight());

	SDL_RenderPresent(menuRenderer);
}

void Menu::ExitState() {
	// ensures everyhting in the state is destroyed
	menuRenderer = NULL;
	_gameManager = NULL;
	background.reset();
	menuUi.reset();
}
