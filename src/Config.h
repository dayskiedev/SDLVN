#ifndef CONFIG_H
#define CONFIG_h

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int CHOICE_BUTTON_WIDTH;
extern int CHOICE_BUTTON_HEIGHT;

// should not be const as they can be changed in a seperate config.txt ?
extern std::string GLOBAL_FONT_PATH;
extern std::string GLOBAL_BACKGROUNDS_PATH;
extern std::string GLOBAL_SPRITES_PATH;
extern std::string GLOBAL_SCRIPTS_PATH;

extern std::string DEFAULT_BUTTON_TEXTURE;

// text position
// choice button position
// sprite scale
// sprite positioning
// default font
// button background

#endif