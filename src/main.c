#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

const char * fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";

static PlaydateAPI *pd = NULL;
static LCDFont * font = NULL;

int eventHandler(PlaydateAPI * playdate, PDSystemEvent event, uint32_t arg) {
  (void)arg; // arg is currently only used for event = kEventKeyPressed

  if (event == kEventInit) {
    // Note: If you set an update callback in the kEventInit handler, the system
    // assumes the game is pure C and doesn't run any Lua code in the game
    pd = playdate;
    pd -> display -> setRefreshRate(0);
    pd -> system -> setUpdateCallback(update, pd);

    // load font
    const char * err;
    font = pd -> graphics -> loadFont(fontpath, & err);
    if (font == NULL) {
      pd -> system -> error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
    }

  }

  return 0;
}

static int update(void * userdata) {
  pd -> system -> drawFPS(0, 0);
  return 1;
}

