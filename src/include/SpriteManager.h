#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "Sprite.h"
#include "Config.h"

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();

	void setRenderer(SDL_Renderer* renderer);
	void setSpriteTexPath(std::string spritesTexPath);
	std::string getSpriteTexPath() { return _spritesTexPath; }

	std::vector<std::shared_ptr<Sprite>> getSpriteVector();

	void addSprite(std::string spriteObjName, std::string spriteTexName, std::string screenPos, double spriteScale);
	void addSprite(std::string spriteObjName, std::string spriteTextName, double spriteScale, int x, int y, int w, int h);

	void setSprite(std::string spriteObjName, std::string spriteName);
	void removeSprite(std::string spriteObjName);

	std::vector<std::shared_ptr<Sprite>>::iterator findSpriteByName(std::string spriteName);

	std::vector<std::shared_ptr<Sprite>> GetSprites();

private:
	std::vector<std::shared_ptr<Sprite>> _sprites;

	SDL_Renderer* _renderer = NULL;
	std::string _spritesTexPath = "";

	std::unordered_map<std::string, std::pair<int,int>> _spritePositions = {
		{"CENTRE",		{RELATIVE_SCREEN_WIDTH / 2,	RELATIVE_SCREEN_HEIGHT / 2}},
		{"CENTRE_STAGE", {RELATIVE_SCREEN_WIDTH / 2, RELATIVE_SCREEN_HEIGHT}},
		{"LEFT",		{RELATIVE_SCREEN_WIDTH / 4,	RELATIVE_SCREEN_HEIGHT}},
		{"RIGHT",		{RELATIVE_SCREEN_WIDTH / 4 + (RELATIVE_SCREEN_WIDTH / 2), RELATIVE_SCREEN_HEIGHT}}
	};
};