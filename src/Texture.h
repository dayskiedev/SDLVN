#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
public:
	Texture();
	Texture(SDL_Renderer* renderer, std::string texturePath, int w, int h, int x, int y);
	~Texture();
	
	void setRenderer(SDL_Renderer* _renderer);
	void setFont(TTF_Font* _font);

	void setColour(Uint8 r, Uint8 g, Uint8 b);

	void setAlpha(Uint8 a);

	void render();
	void render(int x, int y);
	void render(int x, int y, int w, int h);

	// might as well be public right?
	int getWidth();
	int getHeight();
	int getX();
	int getY();

	void setX(int x);
	void setY(int y);
	void setWidth(int w);
	void setHeight(int h);

	// refactor these to the sprite class 
	bool loadFromFile(std::string path);

	bool loadFromRenderedText(std::string text, SDL_Color textColour);

	void free();

private:
	SDL_Texture* mTexture = NULL;
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;

	int mWidth;
	int mHeight;
	int mX;
	int mY;
};

#endif