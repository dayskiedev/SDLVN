#include <iostream>

#include "Config.h"

const std::string PROGRAM_NAME = "SDLVN";

const int SAVE_VERSION = 1;

int RELATIVE_SCREEN_WIDTH = 1280;
int RELATIVE_SCREEN_HEIGHT = 720;

double RESOLUTION_SCALE = 1;
bool FULLSCREEN = false;

int CHOICE_BUTTON_WIDTH = 500;
int CHOICE_BUTTON_HEIGHT = 150;

// SAVE DATA DEFAULT INFORMATION FOR NEW GAME
int _SCRIPT_LINE = 0;
std::string _SCRIPT_PATH = "assets/scripts/test_story.vns";
std::string _BACKGROUND_PATH = "assets/backgrounds/dojo.png";

double DEFAULT_TEXT_SPEED = 1.5;

std::string GLOBAL_FONT_PATH = "assets/fonts/sazanami-gothic.ttf";
std::string GLOBAL_BACKGROUNDS_PATH = "assets/backgrounds/";
std::string GLOBAL_SPRITES_PATH = "assets/sprites/";
std::string GLOBAL_SCRIPTS_PATH = "assets/scripts/";
std::string GLOBAL_SOUNDS_PATH = "assets/sounds/";

std::string DEFAULT_BUTTON_TEXTURE = "assets/sprites/sans.png";

std::string DEFAULT_SAVE_LOCATION = "assets/saves/";

int MUSIC_VOLUME = 100;
int SFX_VOLUME = 100;