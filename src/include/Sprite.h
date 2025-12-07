#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"

#ifndef SPRITE_H
#define SPRITE_H


class Sprite : public Texture {
public:
	Sprite();
	Sprite(std::string spriteName, std::string spriteTexPath, int x, int y, int w, int h, SDL_Renderer* renderer);
	//~Sprite();

	void SetSpriteName(std::string spriteName);
	std::string GetSpriteName();

	void SetSpritePath(std::string spritePath);
	std::string GetSpriteTexPath();

private:
	std::string _spriteName;
	std::string _spriteTexPath;
};

#endif