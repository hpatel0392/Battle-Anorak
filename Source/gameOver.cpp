#include "gameOver.h"
#include "gamedata.h"
#include "ioMod.h"
#include "renderContext.h"



GameOver::GameOver(bool w):
  io( IOmod::getInstance() ),
  renderer(RenderContext::getInstance().getRenderer()),
  win(w),
  width(Gamedata::getInstance().getXmlInt("view/width")),
  height(Gamedata::getInstance().getXmlInt("view/height")),
  alpha(0)
{}


void GameOver::draw() const{
  if(win){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
    SDL_Rect rect = {0, 0, width, height};
    SDL_RenderFillRect(renderer, &rect);

    SDL_Color c = {0,0,0,255};
  
    io.writeGameOver("YOU WIN!",c, width/2 - 400, height/2 - 150);
    io.writeText("Press 'R' to restart",c, width/2 - 55, height-25);
  } else {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
    SDL_Rect rect = {0, 0, width, height};
    SDL_RenderFillRect(renderer, &rect);

    SDL_Color c = {255,255,255,255};
  
    io.writeGameOver("GAME OVER", c, width/2 - 450, height/2 - 150);
    io.writeText("Press 'R' to restart", c, width/2 - 55, height-25);
  }
}

void GameOver::update(){
  if(alpha < 220)
     ++alpha;  
}

