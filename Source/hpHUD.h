#ifndef HPHUD_H
#define HPHUD_H

#include <SDL.h>
#include "ioMod.h"
#include "player.h"
#include "boss.h"

class HpHUD{
public:
  HpHUD(const Player *, const Boss *);  

  void draw() const;
private:
  const IOmod& io;
  SDL_Renderer * const renderer;
  const Player * player;
  const Boss * boss;
  const int playerMaxHP;
  const int bossMaxHP;
  const int barWidth;
  const int barHeight;
};
#endif
