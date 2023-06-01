#include <pd_api.h>
#include <stdint.h>
#include <stdbool.h>
#include "kick.h"
#include "snare.h"

#define SNARE_DECAY 0.20
#define SNARE_HZ 440

typedef struct GameData {
  // Frame Data
  uint32_t frame;
  float last_time;
  float delta_time;

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
bool button_pressed(PDButtons button);
void game_update(void);
