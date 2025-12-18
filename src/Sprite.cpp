#include "Sprite.h"

// only thing this is different to the texture is name
// becayse of this name we can access function to change the sprite.
// should those functions be in the interpretor or this class?

Sprite::Sprite(){}
Sprite::Sprite(std::string spriteName, std::string spriteTexPath, int x, int y, int w, int h, SDL_Renderer* renderer) {
	setRenderer(renderer); // needs to be assigned first so that textures can be created
	SetSpriteName(spriteName);
	SetSpritePath(spriteTexPath);
	loadFromFile(spriteTexPath);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
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

void Sprite::Render() {
	Texture::Render();
}

void Sprite::Render(double x, double y) {
	Texture::Render(x, y);
}

void Sprite::Render(double x, double y, double w, double h) {
	Texture::Render(x, y, w, h);
}

std::string Sprite::GetSpriteName() { return _spriteName; }
std::string Sprite::GetSpriteTexPath() { return _spriteTexPath; }

void Sprite::SetSpriteScale(double scale) {
	_spriteScale = scale;
	setWidth(getWidth() * scale);
	setHeight(getHeight() * scale);

	// we want to leave them anchored to the bottom of the screen so we need to reset the y with this new scale
	setY(RELATIVE_SCREEN_HEIGHT - getHeight());
}