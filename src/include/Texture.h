#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture {
public:
	Texture();
	Texture(SDL_Renderer* renderer, std::string texturePath, int w, int h, int x, int y);
	virtual ~Texture();
	
	void setRenderer(SDL_Renderer* _renderer);
	void setFont(TTF_Font* _font);

	void setColour(Uint8 r, Uint8 g, Uint8 b);

	void setAlpha(Uint8 a);

	Uint8 getAlpha();

	virtual void Render();
	virtual void Render(double x, double y);
	virtual void Render(double x, double y, double w, double h);

	// this should NOT be in texture class, should make some sort of gameobject
	// base class that includes texture that everyhting should derive from?
	virtual void Update(SDL_Event e);
	
	// load new texture while keeping the same width and height (cant beleive it took this long to put in)
	void ChangeTexture(std::string pathToTexture);

	// might as well be public right?
	double getWidth();
	double getHeight();
	double getX();
	double getY();

	void setX(double x);
	void setY(double y);
	void setWidth(double w);
	void setHeight(double h);

	// refactor these to the sprite class 
	bool loadFromFile(std::string path);

	bool loadFromRenderedText(std::string text, SDL_Color textColour);

	void free();
	void freeFont();
private:
	SDL_Texture* mTexture = NULL;
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;

	double mWidth;
	double mHeight;
	double mX;
	double mY;
	Uint8 alpha;
};