#include <pd_api.h>

#define KICK_DECAY 0.15
#define KICK_HZ 80

typedef struct KickModule {
  PDSynth *synth;
  LCDBitmap *bitmap;
  LCDSprite *sprite;
} KickModule;

void init_kick_module(PlaydateAPI *playdate);
KickModule get_kick_module(void);
void hit_kick(PlaydateAPI *playdate);
