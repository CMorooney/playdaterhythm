#include <pd_api.h>
#include "kick.h"
#include "snare.h"

void init_drawing(PlaydateAPI *playdate);

void draw_road(void);
void add_new_road_line(void);
void road_line_sprite_update(LCDSprite* sprite);
void draw_road_line(LCDSprite* sprite, PDRect bounds, PDRect drawRect);

void create_kick_note(KickModule module);
void create_snare_note(SnareModule module);

void update_notes(void);
void note_sprite_update(LCDSprite* sprite);
