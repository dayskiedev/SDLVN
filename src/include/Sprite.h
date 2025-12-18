#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"

class Sprite : public Texture {
public:
	Sprite();
	Sprite(std::string spriteName, std::string spriteTexPath, int x, int y, int w, int h, double spriteScale, SDL_Renderer* renderer);
	//~Sprite();

	void SetSpriteName(std::string spriteName);
	std::string GetSpriteName();

	void SetSpritePath(std::string spritePath);
	std::string GetSpriteTexPath();

	double GetScale() { return _spriteScale; }
	void SetSpriteScale(double scale);

private:
	std::string _spriteName;
	std::string _spriteTexPath;
	double _spriteScale = 1.0;

	int baseWidth;
	int baseHeight;
};