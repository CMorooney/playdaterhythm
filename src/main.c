#include "game.h"
#include "pd_api.h"

static int update(void *userdata);

int eventHandler(PlaydateAPI *playdate, PDSystemEvent event, uint32_t arg) {
  (void)arg; // silence warning

  if (event == kEventInit) {
    setup(playdate);
    game_init();
    playdate -> system -> setUpdateCallback(update, playdate);
  }

  return 0;
}

static int update(void *userdata) {
  game_update();
  return 1;
}
