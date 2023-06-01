#include <pd_api.h>
#include <stdint.h>
#include "kick.h"

#define SNARE_DECAY 0.20
#define SNARE_HZ 440

typedef struct GameData {
  // Frame Data
  uint32_t frame;
  float last_time;
  float delta_time;

  // Input Data
  PDButtons buttonsHeld;
  PDButtons buttonsPressed;
  PDButtons buttonsReleased;

  // Synths
  PDSynth *snareSynth;
  KickModule kickModule;

  // Assets
  LCDFont* font;
} GameData;

void setup(PlaydateAPI *pd);
void game_init(void);
void game_update(void);
void initFont(void);
void initBitmaps(void);
void initSprite(void);
void initKick(void);
void initSnare(void);
void updateDeltaTime(void);
void updateButtons(void);
void buttonsPressed(void);
void game_update(void);
