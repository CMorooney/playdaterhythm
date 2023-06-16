#include "drawing.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define BEAT_LINE_HEIGHT 16
#define MARKER_SIZE 16
#define INITIAL_ROAD_WIDTH 44
#define FINAL_ROAD_WIDTH 400
#define ROAD_IMAGE "image/road2.png"

PlaydateAPI *playdate;

LCDPattern grey50 = {
	0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, // Bitmap, each byte is a row of pixel
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Mask, here fully opaque
};

void init_drawing(PlaydateAPI *pd) {
  playdate = pd;
}

void create_note_sprite(LCDBitmap *bitmap, void *embeddedData) {
  LCDSprite *sprite = playdate->sprite->newSprite();

  playdate -> sprite -> setImage(sprite, bitmap, kBitmapUnflipped);
  playdate->sprite->setSize(sprite, MARKER_SIZE, MARKER_SIZE);
  playdate->sprite->moveTo(sprite, SCREEN_WIDTH/2, MARKER_SIZE/2);
  playdate->sprite->setUpdateFunction(sprite, note_sprite_update);
  playdate->sprite->setUserdata(sprite, embeddedData);
  playdate->sprite->addSprite(sprite);
}

void add_new_road_line(void) {
  LCDSprite *sprite = playdate->sprite->newSprite();
  playdate->sprite->moveTo(sprite, SCREEN_WIDTH/2, BEAT_LINE_HEIGHT/2);
  playdate->sprite->setSize(sprite, SCREEN_WIDTH, BEAT_LINE_HEIGHT);
  playdate->sprite->setDrawFunction(sprite, draw_road_line);
  playdate->sprite->setUpdateFunction(sprite, road_line_sprite_update);
  playdate->sprite->addSprite(sprite);
}

void create_kick_note(KickModule module) {
  create_note_sprite(module.bitmap, NULL);
}

void create_snare_note(SnareModule module) {
  create_note_sprite(module.bitmap, NULL);
}

// this is called every game loop iteration
void update_notes(void) {
  playdate->sprite->updateAndDrawSprites();
}

void note_sprite_update(LCDSprite *sprite) {
  float x, y;
  playdate->sprite->getPosition(sprite, &x, &y);

  // sprite is off screen, free from memory and be done
  if(y > SCREEN_HEIGHT + (MARKER_SIZE*2)) {
    playdate->sprite->removeSprite(sprite);
    playdate->sprite->freeSprite(sprite);
    return;
  }

  playdate->sprite->moveBy(sprite, 0, + 2);
}

void road_line_sprite_update(LCDSprite *sprite) {
  float x, y;
  playdate->sprite->getPosition(sprite, &x, &y);

  // sprite is off screen, free from memory and be done
  if(y > SCREEN_HEIGHT + (BEAT_LINE_HEIGHT*2)) {
    playdate->sprite->removeSprite(sprite);
    playdate->sprite->freeSprite(sprite);
    return;
  }

  playdate->sprite->moveBy(sprite, 0, + (y*.01));
}

// bounds is the bounds of the given sprite.
// drawRect is the current dirty rect being updated by the display list.
void draw_road_line(LCDSprite* sprite, PDRect bounds, PDRect drawRect) {
  float growth = .7f * bounds.y;
  float x1 = (SCREEN_WIDTH/2 - INITIAL_ROAD_WIDTH/2) - growth;
  float x2 = (SCREEN_WIDTH/2 + INITIAL_ROAD_WIDTH/2) + growth;
  playdate->graphics->fillRect(x1, bounds.y, SCREEN_WIDTH - (x1*2), (bounds.y*.1), grey50);
  // idk why this isn't working the orderin of this array must be off and maybe also the Fill rule in fillPolygon

  /* int points[8] = { x1, bounds.y, bounds.width - (x1*2), bounds.y, x1, bounds.height, bounds.width - (x1*2), bounds.height }; */
  /* playdate->graphics->fillPolygon(4, points, kColorBlack, kPolygonFillEvenOdd); */
}
