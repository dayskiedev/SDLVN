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
		{"centre",		{RELATIVE_SCREEN_WIDTH / 2,	RELATIVE_SCREEN_HEIGHT / 2}},
		// silly pixel offset i know but idc
		{"centre_stage", {RELATIVE_SCREEN_WIDTH / 2, RELATIVE_SCREEN_HEIGHT + 10}},
		{"left",		{RELATIVE_SCREEN_WIDTH / 4,	RELATIVE_SCREEN_HEIGHT}},
		{"right",		{RELATIVE_SCREEN_WIDTH / 4 + (RELATIVE_SCREEN_WIDTH / 2), RELATIVE_SCREEN_HEIGHT}}
	};
};