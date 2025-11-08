#include <iostream>
#include <vector>

#include "Button.h"
#include "Texture.h"

#ifndef UI_MANAGER
#define UI_MANAGER

class UIManager : public Button {
public:
	// add ui button
	// add choice button
	// move text rendering to here?

	void setRenderer(SDL_Renderer* renderer);
	
	std::vector<Button*> GetUiVector();

	void AddButton(std::string btnName, std::string btnContents, int x, int y, int w, int h);
	void AddButton(Button* button);
	void RemoveButton(std::string btnName);
	void RemoveButtons();

	int GetButtonOffset();

private:
	SDL_Renderer* _renderer = NULL;
	std::vector <Button*> _buttons;
	int _btnOffset = 250;
};


#endif // !UI_MANAGER
