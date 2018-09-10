#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "player.h"
#include "reactor.h"
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "collisionStrategy.h"
#include "HUD.h"
#include "bulletManager.h"
#include "explosionManager.h"
#include "gameOver.h"

Engine::~Engine() { 
  for(auto& r: reactors){
     delete r;
  }
  for(auto& w: world){
    delete w;
  }
  delete hud;
  delete player;
  delete boss;
  delete over;
  delete hpBar;

  explosionManager.reset();
  BulletManager::getInstance().reset();
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( RenderContext::getInstance().getRenderer() ),
  world(),
  viewport( Viewport::getInstance() ),
  player(new Player("Player")),
  boss(new Boss("Godzilla")),
  reactors(),
  collision(false),
  makeVideo( false ),
  hud(new HUD(player)),
  sound(),
  explosionManager(ExplosionManager::getInstance()),
  playerGod(false),
  over(nullptr),
  hpBar(new HpHUD(player, boss) )
{
  world.emplace_back(new World("sky", Gamedata::getInstance().getXmlInt("sky/factor")) );
  world.emplace_back(new World("mountains", Gamedata::getInstance().getXmlInt("mountains/factor")) );
  world.emplace_back(new World("castle", Gamedata::getInstance().getXmlInt("castle/factor")) ); 
 
  player->attach(boss);
  
  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  SDL_RenderClear(renderer);
  
  for(auto& w: world){
    w->draw();
  }

  for(auto& s: reactors){
    s->draw();
  }

  player->draw();
  boss->draw();
  explosionManager.draw();
  hud->draw();
  hpBar->draw();
  viewport.draw();
  

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 200);
  SDL_Rect rect = {25, Gamedata::getInstance().getXmlInt("view/height")-35 , 210, 25};
  SDL_RenderFillRect(renderer, &rect);
  io.writeText("Harsh Patel and Jacob Murphy", {0, 0, 0, 255}, 
               30, Gamedata::getInstance().getXmlInt("view/height")-30);

  if(playerGod){
     io.writeText("God Mode Active", {0xff, 0xd7, 0, 255}, 
       175, 30);
  }
  
  //draw last
  if(over){
    over->draw();
  }


  SDL_RenderPresent(renderer);
 
}

void Engine::checkForCollisions() {
  collision = false;
  auto it = reactors.begin();
  PerPixelCollisionStrategy strategy;

  // collisions non player/boss
  while ( it != reactors.end() ) {
    if( BulletManager::getInstance().collided(static_cast<Drawable*>(*it)) ){
       Reactor* doa = *it;
       player->detach(doa);       
     
       explosionManager.addExplosion(doa->getPosition());
       sound[1];

       delete doa;
       it = reactors.erase(it);

    } else if(strategy.execute(**it, *player)){
       collision = true;
       if(!playerGod){
         player->hit();
       }
       player->collided();
       Reactor* doa = *it;
       player->detach(doa);

       explosionManager.addExplosion(doa->getPosition());
       sound[1];

       delete doa;
       it = reactors.erase(it);
 
    } else ++it;
  }

  // check for collisions with player and boss
  if( BulletManager::getInstance().collided(static_cast<Drawable*>(player)) ){
    player->collided();
    collision = true;
    if(!playerGod){
      player->hit();
    }
    explosionManager.addExplosion(player->getPosition());      
      sound[1];
  } 

  if(  BulletManager::getInstance().collided(static_cast<Drawable*>(boss)) ){
      if(boss->dead()){
        explosionManager.addExplosion(boss->getPosition()+Vector2f(150, -300) );

       } else boss->hit();
         sound[1];
   }
   if(strategy.execute(*boss, *player)){
      player->collided();
      collision = true;
      if(!playerGod){ //running into the boss does 10 damage every frame. (which means you die)
        player->hit(); 
        player->hit();
      }
   }

   if(collision == false){
      player->missed();
   }
   
}

void Engine::update(Uint32 ticks) {
  if(!over){
    if(player->dead()){
      over = new GameOver(false); //lose
      sound[0];
    }
    if(boss->dead())
      over = new GameOver(true); //win
    for(auto& s: reactors){
       s->update(ticks);
    }

    for(auto& w: world){
      w->update();
    }

    checkForCollisions();

    player->update(ticks);
    boss->update(ticks);

    explosionManager.update(ticks);
    hud->update();

    viewport.update();
    
  }else{
    over->update();
  }
   
}



bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  bool restart = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_O] ) {
           sound.toggleMusic();
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDL_SCANCODE_F1]) {
          hud->toggleHUD();
        }
        if (keystate[SDL_SCANCODE_F2]) {
          hud->togglePoolHUD();
        }
        if (keystate[SDL_SCANCODE_G]) {
          playerGod = !playerGod;
        }
        if (keystate[SDL_SCANCODE_R]) {
          restart = true;
          done = true; 
          break;
        }

        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        } else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_A]) {
        player->left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        player->right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      if (keystate[SDL_SCANCODE_SPACE]) {
         player->shoot();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }

  return restart;
}
