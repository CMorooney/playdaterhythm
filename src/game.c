#include "game.h"

PlaydateAPI *playdate;
GameData data;

void setup(PlaydateAPI *pd) {
  playdate = pd;
}

void game_init(void) {
  playdate -> display -> setRefreshRate(0);

  init_drawing(playdate);
  draw_road();
  init_font();
  init_kick();
  init_snare();
}

void init_font(void) {
  const char *err;
  const char * fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
  data.font = playdate -> graphics -> loadFont(fontpath, &err);
  if (data.font == NULL) {
    playdate -> system -> error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
  }
}

void init_kick(void) {
  init_kick_module(playdate);
  data.kick_module = get_kick_module();
}

void init_snare(void) {
  init_snare_module(playdate);
  data.snare_module = get_snare_module();
}

void update_delta_time(void) {
  int current_time = playdate -> system -> getCurrentTimeMilliseconds();
  data.delta_time = current_time - data.last_time;
  data.last_time = current_time;
}

void update_buttons(void) {
  playdate -> system -> getButtonState(&data.buttons_held,
                                       &data.buttons_pressed,
                                       &data.buttons_released);
}

// makes sure button is in buttonsPressed flags
// AND not in buttonsReleased flags
// this should be called after `updateButtons` to ensure those flags are up to date
bool button_pressed(PDButtons button) {
  if(button & data.buttons_pressed && !(button & data.buttons_released)) {
    return true;
  }
  return false;
}

void game_update(void) {
  update_delta_time();
  update_notes();

  update_buttons();

  if(button_pressed(kButtonDown)) {
    hit_kick(playdate);
    create_kick_note(data.kick_module);
  }

  if(button_pressed(kButtonRight)) {
    hit_snare(playdate);
    create_snare_note(data.snare_module);
  }

  playdate -> system -> drawFPS(0, 0);
}

