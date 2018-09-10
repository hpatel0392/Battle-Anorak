#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include "ioMod.h"


class GameOver {
public:
  GameOver (bool);
  
  void draw() const;
  void update();

private:
  const IOmod& io;
  SDL_Renderer * const renderer;
  bool win;
  int width;
  int height;
  int alpha;
};
#endif
