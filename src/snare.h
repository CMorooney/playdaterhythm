#include <pd_api.h>

#define SNARE_DECAY 0.15
#define SNARE_HZ 80

typedef struct SnareModule {
  PDSynth *synth;
  LCDBitmap *bitmap;
  LCDSprite *sprite;
} SnareModule;

void init_snare_module(PlaydateAPI *playdate);
SnareModule get_snare_module(void);
void hit_snare(PlaydateAPI *playdate);
