#include <pd_api.h>
#include <stdint.h>
#include <stdbool.h>
#include "drawing.h"

typedef struct GameData {
  // Time Data
  float last_time;
  float delta_time;
  float time_since_last_beat;// in seconds

  // Input Data
  PDButtons buttons_held;
  PDButtons buttons_pressed;
  PDButtons buttons_released;

  // Synths
  SnareModule snare_module;
  KickModule kick_module;

  // Assets
  LCDFont* font;
} GameData;

void setup(PlaydateAPI *pd);
void game_init(void);
void game_update(void);
void init_font(void);
void init_bitmaps(void);
void init_sprite(void);
void init_kick(void);
void init_snare(void);
void update_delta_time(void);
void update_buttons(void);
bool is_button_pressed(PDButtons button);
void game_update(void);
