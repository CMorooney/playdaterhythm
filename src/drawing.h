#include <pd_api.h>
#include "kick.h"
#include "snare.h"

void init_drawing(PlaydateAPI *playdate);

void add_new_road_line(void);
void road_line_sprite_update(LCDSprite* sprite);
void draw_road_line(LCDSprite* sprite, PDRect bounds, PDRect drawRect);

