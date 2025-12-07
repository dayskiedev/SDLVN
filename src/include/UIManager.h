#include <iostream>
#include <vector>
#include <memory>

#include "Button.h"
#include "Texture.h"

#ifndef UI_MANAGER
#define UI_MANAGER

class UIManager : public Button {
public:
	// add ui button
	// add choice button
	// move text rendering to here?
	~UIManager();

	void setRenderer(SDL_Renderer* renderer);
	SDL_Renderer* getRenderer();
	
	std::vector<std::shared_ptr<Button>> GetUiVector();

	void AddButton(std::string btnName, std::string btnContents, ButtonType type, int x, int y, int w, int h);
	void AddButton(std::shared_ptr<Button> button);
	void RemoveButton(std::string btnName);
	void RemoveButtons();
	void RemoveButtonsByType(ButtonType type);

	int GetButtonOffset();

private:
	SDL_Renderer* _renderer = NULL;
	std::vector <std::shared_ptr<Button>> _buttons;
	int _btnOffset = 250;
};


#endif // !UI_MANAGER
