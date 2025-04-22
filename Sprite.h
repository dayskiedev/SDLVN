#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"

class Sprite : public Texture {
public:
	//Sprite();
	//~Sprite();

	void SetSpriteName(std::string SpriteName);
	std::string GetSpriteName();

private:
	std::string _spriteName;
};
