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

void SpriteManager::addSprite(std::string spriteObjName, std::string spriteTexName, std::string screenPos, double spriteScale) {
	std::shared_ptr<Sprite> sprite(new Sprite);
	sprite->setRenderer(_renderer);

	sprite->SetSpriteName(spriteObjName);
	std::string spritePath = _spritesTexPath + spriteTexName;
	sprite->SetSpritePath(spritePath);
	sprite->loadFromFile(spritePath);

	if (_spritePositions.find(screenPos) == _spritePositions.end()) {
		std::cout << "Unable to find position " << screenPos << " in map, using default value!" << std::endl;
		screenPos = "CENTRE";
	}

	int x_pos = _spritePositions.find(screenPos)->second.first;
	int y_pos = _spritePositions.find(screenPos)->second.second;

	// set sprite scale here:
	sprite->SetSpriteScale(spriteScale);

	// scale sprite textures by this scale
	sprite->setWidth(sprite->getWidth() * sprite->GetScale());
	sprite->setHeight(sprite->getHeight() * sprite->GetScale());
	sprite->setY(RELATIVE_SCREEN_HEIGHT - sprite->getHeight());

	// convert pos to be set from the centre of the sprite
	x_pos = x_pos - (sprite->getWidth() / 2);
	y_pos = y_pos - sprite->getHeight();

	sprite->setX(x_pos);
	sprite->setY(y_pos);

	_sprites.push_back(sprite);
}

void SpriteManager::addSprite(std::string spriteObjName, std::string spriteTextName, double spriteScale, int x, int y, int w, int h) {
	std::shared_ptr<Sprite> sprite(new Sprite(spriteObjName,
		spriteTextName,
		x, y,
		w, h,
		spriteScale,
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
	auto stc = (*spriteToChange);
	stc->loadFromFile(_spritesTexPath + spriteTexName);
	stc->SetSpritePath(_spritesTexPath + spriteTexName);
	stc->SetSpriteScale((*spriteToChange)->GetScale());
	
	stc->setWidth(stc->getWidth() * stc->GetScale());
	stc->setHeight(stc->getHeight() * stc->GetScale());
	stc->setY(RELATIVE_SCREEN_HEIGHT - stc->getHeight());
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