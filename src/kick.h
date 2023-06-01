#include <pd_api.h>

#define KICK_DECAY 0.15
#define KICK_HZ 80

typedef struct KickModule {
  PDSynth *synth;
  LCDBitmap *bitmap;
  LCDSprite *sprite;
} KickModule;

void initKickModule(PlaydateAPI *playdate);
KickModule getKickModule(void);
void hitKick(PlaydateAPI *playdate);
