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

void add_new_road_line(void) {
  LCDSprite *sprite = playdate->sprite->newSprite();

  playdate->sprite->moveTo(sprite, SCREEN_WIDTH/2, BEAT_LINE_HEIGHT/2);
  playdate->sprite->setSize(sprite, 60, 1);
  playdate->sprite->setDrawFunction(sprite, draw_road_line);
  playdate->sprite->setUpdateFunction(sprite, road_line_sprite_update);
  playdate->sprite->addSprite(sprite);
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

  float newWidth = y * 1.8f;
  float newHeight = y * 0.13f;
  float dY = y * .01f;
  playdate->sprite->setSize(sprite, newWidth, newHeight);
  playdate->sprite->moveBy(sprite, 0, + dY);
}

// bounds is the bounds of the given sprite.
// drawRect is the current dirty rect being updated by the display list.
void draw_road_line(LCDSprite* sprite, PDRect bounds, PDRect drawRect) {
  float x1 = bounds.x;
  float y1 = bounds.y;
  float x2 = bounds.x + bounds.width;
  float y2 = bounds.y + bounds.height;
  float inset = y1 * .12f;

  // points seem to do best in counter-clockwise order
  // (in this case starting from upper left corner)
  int points[8] = {
                    x1 + inset, y1,
                    x1, y2,
                    x2, y2,
                    x2 - inset, y1
                  };
  /* playdate->graphics->fillRect(bounds.x, bounds.y, bounds.width, bounds.height, grey50); */
  playdate->graphics->fillPolygon(4, points, kColorBlack, kPolygonFillNonZero);
}
