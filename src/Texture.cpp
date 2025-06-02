// SPLIT THIS INTO TEXT.CPP AND SPRITE.CPP THAT INHERIT FROM THIS
#include "Texture.h"

Texture::Texture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mX = 0;
	mY = 0;
}

Texture::~Texture() {
	free();
}

void Texture::setRenderer(SDL_Renderer* _renderer) {
	renderer = _renderer;
}

void Texture::setFont(TTF_Font* _font) {
	font = _font;
}

void Texture::setColour(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void Texture::setAlpha(Uint8 a) {
	SDL_SetTextureAlphaMod(mTexture, a);
}

// dont need this many variations of the render?

void Texture::render() {
	SDL_Rect renderQuad = { mX,mY, mWidth, mHeight };
	SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

void Texture::render(int x, int y) {
	mX = x;
	mY = y;
	SDL_Rect renderQuad = { x,y, mWidth, mHeight };
	SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}


void Texture::render(int x, int y, int w, int h) {
	mX = x;
	mY = y;
	SDL_Rect renderQuad = { x,y, w, h };
	SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

// might as well be public right?
int Texture::getWidth() { return mWidth; }
int Texture::getHeight() { return mHeight; }
int Texture::getX() { return mX; }
int Texture::getY() { return mY; }

void Texture::setX(int x) { mX = x; }
void Texture::setY(int y) { mY = y; }
void Texture::setWidth(int w) { mWidth = w; }
void Texture::setHeight(int h) { mHeight = h; }

// refactor these to the sprite class 
bool Texture::loadFromFile(std::string path) {
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		std::cout << "Unable to load image: " << IMG_GetError() << std::endl;
	}
	else {
		newTexture = NULL;

		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			std::cout << "Unable to create texture: " << SDL_GetError() << std::endl;
			// keep it as current texture as a failsafe

		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string text, SDL_Color textColour) {
	free();
	// TODO:
	// change this to glyphs, whatever that is
	// lets us render text 1 character at a time
	// need to implement text wrapping

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);
	if (textSurface == NULL) {
		std::cout << "Unable to render text surface: " << TTF_GetError() << std::endl;
	}
	else {
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL) {
			std::cout << "Unable to create texture from surface: " << SDL_GetError() << std::endl;
		}
		else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture;

}

void Texture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
