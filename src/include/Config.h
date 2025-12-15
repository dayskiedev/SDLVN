#pragma once

extern const std::string PROGRAM_NAME;

extern const int SAVE_VERSION;

extern int RELATIVE_SCREEN_WIDTH;
extern int RELATIVE_SCREEN_HEIGHT;

extern double RESOLUTION_SCALE;
extern bool FULLSCREEN;

extern int CHOICE_BUTTON_WIDTH;
extern int CHOICE_BUTTON_HEIGHT;

// SAVE DATA DEFAULT INFORMATION FOR NEW GAME
extern int _SCRIPT_LINE;
extern std::string _SCRIPT_PATH;
extern std::string _BACKGROUND_PATH;

// should not be const as they can be changed in a seperate config.ini ?
extern std::string GLOBAL_FONT_PATH;
extern std::string GLOBAL_BACKGROUNDS_PATH;
extern std::string GLOBAL_SPRITES_PATH;
extern std::string GLOBAL_SCRIPTS_PATH;
extern std::string GLOBAL_SOUNDS_PATH;

extern double DEFAULT_TEXT_SPEED;

extern std::string DEFAULT_BUTTON_TEXTURE;

extern std::string DEFAULT_SAVE_LOCATION;

// text position
// choice button position
// sprite scale
// sprite positioning
// default font
// button background
