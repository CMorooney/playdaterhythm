#include <pd_api.h>
#include "kick.h"
#include "snare.h"

void init_drawing(PlaydateAPI *playdate);
void create_kick_note(KickModule module);
void create_snare_note(SnareModule module);
void update_notes(void);
void sprite_update(LCDSprite* sprite);
