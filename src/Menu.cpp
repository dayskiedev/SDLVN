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
	saveManager = std::make_unique<SaveManager>();

	// i should just be able to make a button constructor to create these buttons
	// so we can do things like set the functions later....
	// text should be an object i can place to.
	std::shared_ptr<Button> playButton(new Button("new", 
		menuRenderer, 
		DEFAULT_BUTTON_TEXTURE, 
		200, 50, 
		(SCREEN_WIDTH / 2) - 100, 
		(SCREEN_HEIGHT / 2) - 50, 
		"New Game", 
		30
	));

	std::shared_ptr<Button> saveButton(new Button("save",
		menuRenderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		(SCREEN_WIDTH / 2) - 100,
		(SCREEN_HEIGHT / 2),
		"Save Game",
		30
	));

	std::shared_ptr<Button> contButton(new Button("load",
		menuRenderer,
		DEFAULT_BUTTON_TEXTURE,
		200,50,
		(SCREEN_WIDTH / 2) - 100,
		(SCREEN_HEIGHT / 2) + 50, 
		"Load Game",
		30
	));

	std::shared_ptr<Button> optButton(new Button("options",
		menuRenderer,
		DEFAULT_BUTTON_TEXTURE,
		200, 50,
		(SCREEN_WIDTH / 2) - 100,
		(SCREEN_HEIGHT / 2) + 100,
		"Options",
		30
	));

	std::shared_ptr<Button> quitButton(new Button("quit", 
		menuRenderer, 
		DEFAULT_BUTTON_TEXTURE, 
		200, 50, 
		(SCREEN_WIDTH / 2) - 100, 
		(SCREEN_HEIGHT / 2) + 150, 
		"Exit", 
		30
	));

	// define on click actions for buttons
	playButton->OnClick = [this]() { _gameManager->ChangeState(std::make_unique<Game>()); };

	saveButton->OnClick = [this]() { saveManager->Save(); };
	contButton->OnClick = [this]() { saveManager->Load(); };

	optButton->OnClick = [this]() { _gameManager->ChangeState(std::make_unique<Options>()); };
	quitButton->OnClick = [this]() { _gameManager->running = false; };
	
	menuUi->AddButton(playButton);
	menuUi->AddButton(saveButton);
	menuUi->AddButton(contButton);
	menuUi->AddButton(optButton);
	menuUi->AddButton(quitButton);

	// these load the textures but they do not get shown?
	background = std::make_unique<Texture>(
		menuRenderer, 
		"backgrounds/umabackground2.png", 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		0, 
		0
	);
}

void Menu::Update(SDL_Event e, double deltaTime) {
	for (auto b : menuUi->GetUiVector()) { b->Update(e); }
}

void Menu::Render() {
	SDL_SetRenderDrawColor(menuRenderer, 100, 100, 100, 100);
	SDL_RenderClear(menuRenderer);

	background->render();

	for (auto b : menuUi->GetUiVector()) { 
		b->render(); 
		// why is this seperate lol?
		b->showText();
	}

	SDL_RenderPresent(menuRenderer);
}

void Menu::ExitState() {
	// placeholder
}
