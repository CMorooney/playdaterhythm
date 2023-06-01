#include "game.h"
#include <stdbool.h>

PlaydateAPI *playdate;
GameData data;

void setup(PlaydateAPI *pd) {
  playdate = pd;
}

void game_init(void) {
  playdate -> display -> setRefreshRate(0);
  playdate -> system -> setUpdateCallback(update, playdate);

  initFont();
  initKick();
  initSnare();
}

void initFont(void) {
  const char *err;
  const char * fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
  data.font = playdate -> graphics -> loadFont(fontpath, &err);
  if (data.font == NULL) {
    playdate -> system -> error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
  }
}

void initKick(void) {
  initKickModule(playdate);
  data.kickModule = getKickModule();
}

void initSnare(void) {
  playdate -> system -> logToConsole("init snareSynth");
  data.snareSynth = playdate -> sound -> synth -> newSynth();
  if (data.snareSynth == NULL) {
    playdate -> system -> error("Couldn't create snareSynth");
  } else {
    playdate -> sound -> synth -> setWaveform(data.snareSynth, kWaveformNoise);
    playdate -> sound -> synth -> setAttackTime(data.snareSynth, 0);
    playdate -> sound -> synth -> setDecayTime(data.snareSynth, SNARE_DECAY);
  }
}

void updateDeltaTime(void) {
  int current_time = playdate -> system -> getCurrentTimeMilliseconds();
  data.delta_time = current_time - data.last_time;
  data.last_time = current_time;
}

void updateButtons(void) {
  playdate -> system -> getButtonState(&data.buttonsHeld,
                                       &data.buttonsPressed,
                                       &data.buttonsReleased);
}

// makes sure button is in buttonsPressed flags
// AND not in buttonsReleased flags
// this should be called after `updateButtons` to ensure those flags are up to date
bool buttonPressed(PDButtons button) {
  if(button & data.buttonsPressed && !(button & data.buttonsReleased)) {
    return true;
  }
  return false;
}

void game_update(void) {
  updateDeltaTime();
  updateButtons();

  //drawTrack();
  //drawBar();

  if(buttonPressed(kButtonDown)) {
    hitKick(playdate);
  }

  if(buttonPressed(kButtonRight)) {
    playdate -> system -> logToConsole("RIGHT PRESSED: playing snare");
    playdate -> sound -> synth -> playNote(data.snareSynth, SNARE_HZ, 1, SNARE_DECAY, 0);
  }

  playdate -> system -> drawFPS(0, 0);
}

