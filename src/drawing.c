#include "drawing.h"
#include "game.h"
#include <pd_api.h>

#define MAX_SPRITES 100
#define SCREEN_WIDTH 420
#define SCREEN_HEIGHT 200

PlaydateAPI *playdate;
LCDSprite *sprites[MAX_SPRITES];

void init_drawing(PlaydateAPI *pd) {
  playdate = pd;
}

void create_note(enum Drum drum, int dx) {
}
