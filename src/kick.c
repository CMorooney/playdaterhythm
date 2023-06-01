#include "kick.h"

KickModule module;

void init_kick_module(PlaydateAPI *playdate) {
  const char *err;
  module.bitmap = playdate -> graphics -> loadBitmap("image/kick.png", &err);
  if(module.bitmap == NULL) {
    playdate -> system -> error("%s:%i Couldn't load kick bitmap %s: %s", __FILE__, __LINE__, "image/kick.png", err);
  }


  module.synth = playdate -> sound -> synth -> newSynth();
  if (module.synth == NULL) {
    playdate -> system -> error("Couldn't create kickSynth");
  } else {
    playdate -> sound -> synth -> setWaveform(module.synth, kWaveformNoise);
    playdate -> sound -> synth -> setAttackTime(module.synth, 0);
    playdate -> sound -> synth -> setDecayTime(module.synth, KICK_DECAY);
  }
}

KickModule get_kick_module(void) {
  return module;
}

void hit_kick(PlaydateAPI *playdate) {
  playdate -> sound -> synth -> playNote(module.synth, KICK_HZ, 1, KICK_DECAY, 0);
}
