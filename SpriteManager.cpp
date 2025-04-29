#include "SpriteManager.h"

SpriteManager::SpriteManager() {}

SpriteManager::~SpriteManager() {
	for (auto sprite : _sprites) {
		delete sprite;
	}
	_sprites.clear();
}

void SpriteManager::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

void SpriteManager::setSpriteTexPath(std::string spritesTexPath) {
	_spritesTexPath = spritesTexPath;
}

std::vector<Sprite*> SpriteManager::getSpriteVector() {
	return _sprites;
}

void SpriteManager::addSprite(std::string spriteObjName, std::string spriteTexName, std::string screenPos) {
	// look into changing this to a smart pointer / object?
	Sprite* sprite = new Sprite;

	// this could all be in a constructor?
	sprite->setRenderer(_renderer);

	sprite->SetSpriteName(spriteObjName);
	std::string spritePath = _spritesTexPath + spriteTexName;
	sprite->loadFromFile(spritePath);
	// get screen positons from dictonary/enum? hardcoded for now which is a big nono
	// screen width / 2 - 200
	// screen height / 2 - 250
	// NEED TO TAKE INTO ACCOUNT SCREEN WIDTH/HEIGHT
	// AS WELL AS SPRITE WIDTH/HEIGHT!!!!! THE PROBELM IS THAT THE
	// SPRTIES ARE SCALED DOWN AT RENDER, THEY SHOULD BE SCALED DOWN HERE!!!!
	sprite->setX(440);
	sprite->setY(110);

	_sprites.push_back(sprite);
}

void SpriteManager::setSprite(std::string spriteObjName, std::string spriteTexName) {
	// check if spritepath is valid
	// check if sprite name matches any in spritelist

	auto spriteToChange = findSpriteByName(spriteObjName);
	if (spriteToChange == _sprites.end()) {
		std::cout << "Unable to change sprite object, " << spriteObjName << " not found!" << std::endl;
		return;
	}
	(*spriteToChange)->loadFromFile(_spritesTexPath + spriteTexName);
}

void SpriteManager::removeSprite(std::string spriteObjName) {
	// chanfe to using a sprite name
	auto spriteToErase = findSpriteByName(spriteObjName);
	if (spriteToErase == _sprites.end()) {
		std::cout << "Unable to remove sprite object, " << spriteObjName << " not found!" << std::endl;
		return;
	}

	delete (*spriteToErase);
	_sprites.erase(spriteToErase);
}

std::vector<Sprite*>::iterator SpriteManager::findSpriteByName(std::string spriteName) {
	// does this NEED to be an iterator? Can i not just use the for auto loop?
	auto vecSpriteElement = std::find_if(_sprites.begin(), _sprites.end(),
		[spriteName](Sprite* s) {
			return s->GetSpriteName() == spriteName;
		});

	if (vecSpriteElement != _sprites.end()) {
		// not sure why it needed the brackets
		return vecSpriteElement;
	}
	else {
		std::cout << "Unable to find sprite obj. " << spriteName << " not found!" << std::endl;;
		return _sprites.end();
	}
}