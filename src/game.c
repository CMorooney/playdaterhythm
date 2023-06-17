#include "game.h"

PlaydateAPI *playdate;
GameData data;

#define BPM 120
#define BPS BPM/60.0f

void setup(PlaydateAPI *pd) {
  playdate = pd;
}

void game_init(void) {
  playdate -> display -> setRefreshRate(0);

  data.time_since_last_beat = -1;
  init_drawing(playdate);
  init_kick();
  init_snare();
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

// returns true if a new beat marker should be drawn.
// currently based on beats-per-second macro, but we likely need a lot more precision
bool update_beat_time(void) {
  if(data.time_since_last_beat == -1 || data.time_since_last_beat >= BPS/5) {
    data.time_since_last_beat = 0;
    playdate->system->resetElapsedTime();
    return true;
  } else {
    data.time_since_last_beat = playdate->system->getElapsedTime();
    return false;
  }
}

void update_buttons(void) {
  playdate -> system -> getButtonState(&data.buttons_held,
                                       &data.buttons_pressed,
                                       &data.buttons_released);
}

// makes sure button is in buttonsPressed flags
// AND not in buttonsReleased flags
// this should be called after `updateButtons` to ensure those flags are up to date
bool is_button_pressed(PDButtons button) {
  if(button & data.buttons_pressed && !(button & data.buttons_released)) {
    return true;
  }
  return false;
}

// main game loop
void game_update(void) {
  update_delta_time();

  bool newBeat = update_beat_time();
  if(newBeat) {
    add_new_road_line();
  }

  playdate->sprite->updateAndDrawSprites();

  update_buttons();

  if(is_button_pressed(kButtonDown)) {
    hit_kick(playdate);
  }

  if(is_button_pressed(kButtonRight)) {
    hit_snare(playdate);
  }

  playdate -> system -> drawFPS(0, 0);
}

