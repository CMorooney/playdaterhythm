#include <stdio.h>
#include <stdlib.h>
#include "pd_api.h"

const char * fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";

static PlaydateAPI * pd = NULL;
static PDSynth * synth = NULL;
static LCDFont * font = NULL;

static int update(void * userdata);
void initFont(void);
void initSynth(void);

int eventHandler(PlaydateAPI * playdate, PDSystemEvent event, uint32_t arg) {
  (void)arg; // arg is currently only used for event = kEventKeyPressed

  if (event == kEventInit) {
    // Note: If you set an update callback in the kEventInit handler, the system
    // assumes the game is pure C and doesn't run any Lua code in the game
    pd = playdate;
    pd -> display -> setRefreshRate(0);
    pd -> system -> setUpdateCallback(update, pd);

    initFont();
    initSynth();
  }

  return 0;
}

void initFont(void) {
  const char * err;
  font = pd -> graphics -> loadFont(fontpath, & err);
  if (font == NULL) {
    pd -> system -> error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
  }
}

void initSynth(void) {
  pd -> system -> logToConsole("init synth");
  synth = pd -> sound -> synth -> newSynth();
  if (synth == NULL) {
    pd -> system -> error("Couldn't create synth");
  } else {
    pd -> sound -> synth -> setWaveform(synth, kWaveformNoise);
    pd -> sound -> synth -> setAttackTime(synth, 0);
    pd -> sound -> synth -> setDecayTime(synth, 10);
    pd -> sound -> synth -> playNote(synth, 440, 1, -1, 0);
    pd -> system -> logToConsole("playing note");
  }
}

static int update(void * userdata) {
  pd -> system -> drawFPS(0, 0);
  return 1;
}

