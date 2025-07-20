#include <iostream>
#include <unordered_map>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "Sprite.h"
#include "Config.h"


#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();

	void setRenderer(SDL_Renderer* renderer);
	void setSpriteTexPath(std::string spritesTexPath);

	std::vector<Sprite*> getSpriteVector();

	void addSprite(std::string spriteObjName, std::string spriteTexName, std::string screenPos);
	void setSprite(std::string spriteObjName, std::string spriteName);
	void removeSprite(std::string spriteObjName);

	std::vector<Sprite*>::iterator findSpriteByName(std::string spriteName);


private:
	std::vector<Sprite*> _sprites;
	SDL_Renderer* _renderer = NULL;
	std::string _spritesTexPath = "";

	std::unordered_map<std::string, std::pair<int,int>> _spritePositions = {
		{"CENTRE",		{SCREEN_WIDTH / 2,	SCREEN_HEIGHT / 2}},
		{"CENTRE_DOWN", {SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 200}},
		{"LEFT",		{SCREEN_WIDTH / 3,	SCREEN_HEIGHT / 2}},
		{"RIGHT",		{SCREEN_WIDTH,		SCREEN_HEIGHT / 2}}

	};
};

#endif