#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include "ioMod.h"
#include "player.h"

class HUD {
public:
  HUD (const Player *);
  
  void draw() const;
  void update();
  void toggleHUD();
  void togglePoolHUD();

private:
  const IOmod& io;
  SDL_Renderer * const renderer;


  int width;
  int height;
  int xLoc;
  int yLoc;
  bool show;
  bool start;

  int poolwidth;
  int poolheight;
  int poolxLoc;
  int poolyLoc;
  bool showPoolHud;

  const Player* player;
};
#endif
