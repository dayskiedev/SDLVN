#include "Sprite.h"

// only thing this is different to the texture is name
// becayse of this name we can access function to change the sprite.
// should those functions be in the interpretor or this class?

Sprite::Sprite(){}
Sprite::Sprite(std::string spriteName, std::string spriteTexPath, int x, int y, int w, int h, SDL_Renderer* renderer) {
	SetSpriteName(spriteName);
	SetSpritePath(spriteTexPath);
	loadFromFile(spriteTexPath);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
	setRenderer(renderer);
}

//
//Sprite::~Sprite() {
//	std::cout << "Remvoing sprite\n";
//}

void Sprite::SetSpriteName(std::string spriteName) {
	_spriteName = spriteName;
}

void Sprite::SetSpritePath(std::string spritePath) {
	_spriteTexPath = spritePath;
}

std::string Sprite::GetSpriteName() { return _spriteName; }
std::string Sprite::GetSpriteTexPath() { return _spriteTexPath; }