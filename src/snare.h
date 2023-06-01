#include <pd_api.h>

#define SNARE_DECAY 0.20
#define SNARE_HZ 440

typedef struct SnareModule {
  PDSynth *synth;
  LCDBitmap *bitmap;
} SnareModule;

void init_snare_module(PlaydateAPI *playdate);
SnareModule get_snare_module(void);
void hit_snare(PlaydateAPI *playdate);
