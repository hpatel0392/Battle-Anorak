#include <iostream>
#include <sstream>
#include "HUD.h"
#include "gamedata.h"
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "player.h"


HUD::HUD(const Player * p):
  io( IOmod::getInstance() ),
  renderer(RenderContext::getInstance().getRenderer()),
  width(Gamedata::getInstance().getXmlInt("HUD/width")),
  height(Gamedata::getInstance().getXmlInt("HUD/height")),
  xLoc(10),
  yLoc(10),
  show(true),
  start(true),

  poolwidth(Gamedata::getInstance().getXmlInt("HUD/width")),
  poolheight(Gamedata::getInstance().getXmlInt("HUD/height")),
  poolxLoc(Gamedata::getInstance().getXmlInt("view/width")-poolwidth-10),
  poolyLoc(10),
  
  showPoolHud(true),
  player(p)
{}


void HUD::toggleHUD(){
  show = !show;
}
  
void HUD::togglePoolHUD(){
  showPoolHud = !showPoolHud;
}

void HUD::draw() const {
  
  if(show){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 150, 150, 255, 170);
    SDL_Rect rect = {xLoc, yLoc, width, height};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    
    std::stringstream str;
    str << "fps: " << Clock::getInstance().getFps();

    io.writeText(str.str(), xLoc + 5, yLoc + 5);    
    io.writeText("w -> up", xLoc + 5, yLoc+25);
    io.writeText("a -> left", xLoc + 5, yLoc+45);
    io.writeText("s -> down", xLoc + 5, yLoc+65);
    io.writeText("d -> right", xLoc + 5, yLoc+85);
    io.writeText("spacebar -> shoot", xLoc + 5, yLoc+105);
    io.writeText("F1 -> Toggle HUD", xLoc + 5, yLoc+125);
  }

  if(showPoolHud){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 150, 150, 255, 170);
    SDL_Rect rect = {poolxLoc, poolyLoc, poolwidth, poolheight/2};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    
   std::stringstream str;
    str << "BulletList: " << player->getGun().blSize();

    io.writeText(str.str(), poolxLoc + 5, yLoc + 5);    
    str.str("");
    str << "FreeList: " << player->getGun().flSize();
    
    io.writeText(str.str(), poolxLoc + 5, poolyLoc+25);
    io.writeText("f2 to toggle", poolxLoc + 5, poolyLoc+45);

  }
}


void HUD::update(){
  if(start){
    if(static_cast<float>(Clock::getInstance().getTicks())*.001 > 3){
      show = false;
      showPoolHud = false;
      start = false;
    }
  }
}
