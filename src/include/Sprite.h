#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"
#include "Config.h"

class Sprite : public Texture {
public:
	Sprite();
	Sprite(std::string spriteName, std::string spriteTexPath, int x, int y, int w, int h, SDL_Renderer* renderer);
	//~Sprite();

	void Render();
	void Render(double x, double y);
	void Render(double x, double y, double w, double h);

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
};