#include "SpriteManager.h"
#include "TextManager.h"
#include "Interpreter.h"

#include "Config.h"

class Game {
public:
	void Run(SDL_Event e, double deltaTime); 
	void Update(SDL_Event e, double deltaTime);
	void Render();
private:
};