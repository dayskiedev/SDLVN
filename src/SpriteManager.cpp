#include "SpriteManager.h"

SpriteManager::SpriteManager() {}

SpriteManager::~SpriteManager() {
	// using unqiue pointers so they will get auto deleted
	_sprites.clear();
}

void SpriteManager::setRenderer(SDL_Renderer* renderer) {
	_renderer = renderer;
}

void SpriteManager::setSpriteTexPath(std::string spritesTexPath) {
	_spritesTexPath = spritesTexPath;
}

std::vector<std::shared_ptr<Sprite>> SpriteManager::getSpriteVector() {
	return _sprites;
}

void SpriteManager::addSprite(std::string spriteObjName, std::string spriteTexName, std::string screenPos) {
	std::shared_ptr<Sprite> sprite(new Sprite);

	// this could all be in a constructor?
	sprite->setRenderer(_renderer);

	sprite->SetSpriteName(spriteObjName);
	std::string spritePath = _spritesTexPath + spriteTexName;
	sprite->SetSpritePath(spritePath);
	sprite->loadFromFile(spritePath);
	// get screen positons from dictonary/enum? hardcoded for now which is a big nono
	// screen width / 2 - 200
	// screen height / 2 - 250
	// NEED TO TAKE INTO ACCOUNT SCREEN WIDTH/HEIGHT
	// AS WELL AS SPRITE WIDTH/HEIGHT!!!!! THE PROBELM IS THAT THE
	// SPRTIES ARE SCALED DOWN AT RENDER, THEY SHOULD BE SCALED DOWN HERE!!!!

	// take into account sprite position from string>

	// works but is theree

	if (_spritePositions.find(screenPos) == _spritePositions.end()) { 
		std::cout << "Unable to find position " << screenPos << " in map, using default value!" << std::endl; 
		screenPos = "CENTRE";
	}

	int x_pos = _spritePositions.find(screenPos)->second.first;
	int y_pos = _spritePositions.find(screenPos)->second.second;

	x_pos = x_pos -  (sprite->getWidth() / 3.5);
	y_pos = y_pos -  (sprite->getHeight() / 3.5);

	sprite->setX(x_pos);
	sprite->setY(y_pos);

	_sprites.push_back(sprite);
}

void SpriteManager::addSprite(std::string spriteObjName, std::string spriteTextName, int x, int y, int w, int h) {
	std::shared_ptr<Sprite> sprite(new Sprite(spriteObjName,
		spriteTextName,
		x, y,
		w, h,
		_renderer));
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

	// these should just happen together i think......
	(*spriteToChange)->loadFromFile(_spritesTexPath + spriteTexName);
	(*spriteToChange)->SetSpritePath(_spritesTexPath + spriteTexName);
}

void SpriteManager::removeSprite(std::string spriteObjName) {
	// chanfe to using a sprite name
	auto spriteToErase = findSpriteByName(spriteObjName);
	if (spriteToErase == _sprites.end()) {
		std::cout << "Unable to remove sprite object, " << spriteObjName << " not found!" << std::endl;
		return;
	}

	// smart pointer will auto erase at this point	
	_sprites.erase(spriteToErase);
}

std::vector<std::shared_ptr<Sprite>>::iterator SpriteManager::findSpriteByName(std::string spriteName) {
	// does this NEED to be an iterator? Can i not just use the for auto loop?
	auto vecSpriteElement = std::find_if(_sprites.begin(), _sprites.end(),
		[spriteName](std::shared_ptr<Sprite> s) {
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

// return by refernce only if the caller should mutate them, we don't want save to modify directly
std::vector<std::shared_ptr<Sprite>> SpriteManager::GetSprites() { return _sprites; }