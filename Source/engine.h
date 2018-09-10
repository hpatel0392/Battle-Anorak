#ifndef ENGINE_H
#define ENGINE_H


#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "sound.h"
#include "player.h"
#include "reactor.h"
#include "HUD.h"
#include "collisionStrategy.h"
#include "explosionManager.h"
#include "boss.h"
#include "gameOver.h"
#include "hpHUD.h"

class Engine {
public:
  Engine ();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  ~Engine ();
  bool play();

private:
  //const RenderContext& rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  std::vector<World*> world;
  Viewport& viewport;

  Player* player;
  Boss* boss;
  std::vector<Reactor*> reactors;

  bool collision;

  bool makeVideo;

  HUD * hud;
  SDLSound sound;

  ExplosionManager& explosionManager;

  bool playerGod;

  GameOver* over;
  HpHUD * hpBar;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();

};

#endif

