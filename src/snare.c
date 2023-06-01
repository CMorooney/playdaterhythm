#include "snare.h"
#include <pd_api.h>

SnareModule module;

void init_snare_module(PlaydateAPI *playdate) {
  const char *err;
  module.bitmap = playdate -> graphics -> loadBitmap("image/snare.png", &err);
  if(module.bitmap == NULL) {
    playdate -> system -> error("%s:%i Couldn't load snare bitmap %s: %s", __FILE__, __LINE__, "image/snare.png", err);
  }

  module.sprite = playdate -> sprite -> newSprite();
  playdate -> sprite -> setImage(module.sprite, module.bitmap, kBitmapUnflipped);

  module.synth = playdate -> sound -> synth -> newSynth();
  if (module.synth == NULL) {
    playdate -> system -> error("Couldn't create kickSynth");
  } else {
    playdate -> sound -> synth -> setWaveform(module.synth, kWaveformNoise);
    playdate -> sound -> synth -> setAttackTime(module.synth, 0);
    playdate -> sound -> synth -> setDecayTime(module.synth, SNARE_DECAY);
  }
}

SnareModule get_snare_module(void) {
  return module;
}

void hit_snare(PlaydateAPI *playdate) {
  playdate -> sound -> synth -> playNote(module.synth, SNARE_HZ, 1, SNARE_DECAY, 0);
}
