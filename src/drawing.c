#include "drawing.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define MARKER_SIZE 16

PlaydateAPI *playdate;

void init_drawing(PlaydateAPI *pd) {
  playdate = pd;
}

void create_sprite(LCDBitmap *bitmap, void *embeddedData) {
  LCDSprite *sprite = playdate->sprite->newSprite();

  playdate -> sprite -> setImage(sprite, bitmap, kBitmapUnflipped);
  playdate->sprite->setSize(sprite, MARKER_SIZE, MARKER_SIZE);
  playdate->sprite->moveTo(sprite, SCREEN_WIDTH/2, MARKER_SIZE/2);
  playdate->sprite->setUpdateFunction(sprite, sprite_update);
  playdate->sprite->setUserdata(sprite, embeddedData);
  playdate->sprite->addSprite(sprite);
}

void draw_road(void) {
  const char *err;
  LCDBitmap *bitmap = playdate -> graphics -> loadBitmap("image/road.png", &err);
  if (bitmap == NULL) {
    playdate -> system -> error("%s:%i Couldn't road kick bitmap %s: %s", __FILE__, __LINE__, "image/road.png", err);
  }
  LCDSprite *sprite = playdate->sprite->newSprite();
  playdate-> sprite->setImage(sprite, bitmap, kBitmapUnflipped);
  playdate->sprite->moveTo(sprite, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
  playdate->sprite->setSize(sprite, SCREEN_WIDTH, SCREEN_HEIGHT);
  playdate->sprite->addSprite(sprite);
}

void create_kick_note(KickModule module) {
  create_sprite(module.bitmap, NULL);
}

void create_snare_note(SnareModule module) {
  create_sprite(module.bitmap, NULL);
}

// this is called every game loop iteration
void update_notes(void) {
  playdate->sprite->updateAndDrawSprites();
}

void sprite_update(LCDSprite *sprite) {
  float x, y;
  playdate->sprite->getPosition(sprite, &x, &y);

  // sprite is off screen, free from memory and be done
  if(y > SCREEN_HEIGHT + (MARKER_SIZE*2)) {
    playdate->sprite->removeSprite(sprite);
    playdate->sprite->freeSprite(sprite);
    return;
  }

  /* retrieve user data in the sprite?
  void *data = playdate->sprite->getUserData(sprite);
  */

  playdate->sprite->moveBy(sprite, 0, + 2);
}
