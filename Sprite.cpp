#include "Sprite.h"

// only thing this is different to the texture is name
// becayse of this name we can access function to change the sprite.
// should those functions be in the interpretor or this class?

//Sprite::Sprite() :Texture() {
//	_spriteName = "";
//}
//
//Sprite::~Sprite() {
//	std::cout << "Remvoing sprite\n";
//}

void Sprite::SetSpriteName(std::string SpriteName) {
	_spriteName = SpriteName;
}

std::string Sprite::GetSpriteName() { return _spriteName; }