#include <iostream>
#include <sstream>
#include <string>
#include "hpHUD.h"
#include "renderContext.h"
#include "gamedata.h"

HpHUD::HpHUD(const Player * p, const Boss * b):
   io( IOmod::getInstance() ),
   renderer(RenderContext::getInstance().getRenderer()),
   player( p ),
   boss( b ),
   playerMaxHP( p->getHP() ),
   bossMaxHP( b->getHP() ),
   barWidth(Gamedata::getInstance().getXmlInt("hpBar/width") ),
   barHeight(Gamedata::getInstance().getXmlInt("hpBar/height") )
{}


void HpHUD::draw() const {
   static int xLocBoss = Gamedata::getInstance().getXmlInt("view/width") / 2 - barWidth/2;
   static int yLocBoss = 5;
   static int yLocPlayer = yLocBoss + barHeight + 5;
   static int center =  Gamedata::getInstance().getXmlInt("view/width")/2 - 5;
   static std::string bStr("boss");
   static std::string pStr("player");

   auto CalcBarWidth = [this](int hp, std::string& n)->int{
     if(n == "player") return (barWidth-4)*((float)hp/playerMaxHP);
     return (barWidth-4)*((float)hp/bossMaxHP);
   };

   // Draw Boss Health Bar
   SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
   SDL_SetRenderDrawColor(renderer, 0xff, 0x4c, 0x4c, 255);
   SDL_Rect rect = {xLocBoss, yLocBoss, barWidth, barHeight};
   SDL_RenderFillRect(renderer, &rect);
   rect = {xLocBoss-1, yLocBoss-1, barWidth+2, barHeight+2};
   SDL_SetRenderDrawColor(renderer, 0x99, 0, 0, 255);
   SDL_RenderDrawRect(renderer, &rect);
   SDL_SetRenderDrawColor(renderer, 0x66, 0, 0, 255);
   rect = {xLocBoss+2, yLocBoss+1, CalcBarWidth(boss->getHP(), bStr), barHeight-2};
   SDL_RenderFillRect(renderer, &rect);
   io.writeText("Boss", center, yLocBoss+1);

   // draw Player Health Bar
   SDL_SetRenderDrawColor(renderer, 0x4c, 0xff, 0x4c, 255);
   rect = {xLocBoss, yLocPlayer, barWidth, barHeight};
   SDL_RenderFillRect(renderer, &rect);
   rect = {xLocBoss-1, yLocPlayer-1, barWidth+2, barHeight+2};
   SDL_SetRenderDrawColor(renderer, 0, 0x99, 0, 255);
   SDL_RenderDrawRect(renderer, &rect);
   SDL_SetRenderDrawColor(renderer, 0, 0x66, 0, 255);
   rect = {xLocBoss+2, yLocPlayer+1, CalcBarWidth(player->getHP(), pStr), barHeight-2};
   SDL_RenderFillRect(renderer, &rect);
   io.writeText("Player", center, yLocPlayer+1);
}

