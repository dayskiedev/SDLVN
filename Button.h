#include <SDL.h>
#include "Texture.h"

#include <iostream>

class Button {
public:
	void Render();
	void OnClick();

private:
	std::string _name;
	bool _overlapping;
	bool _clicked;

	int _x;
	int _y;
	int _w;
	int _h;
};