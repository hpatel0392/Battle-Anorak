#include "gamedata.h"
#include "explosionManager.h"
#include "sound.h"

ExplosionManager & ExplosionManager::getInstance() {
   static ExplosionManager instance;
   return instance;
}

ExplosionManager::~ExplosionManager() {
   explosionList.clear();
}

void ExplosionManager::reset(){
   explosionList.clear();
}

void ExplosionManager::addExplosion (const Vector2f& v){
   MultiSprite expl("Explosion");
   expl.setVelocityX(0);
   expl.setVelocityY(0);
   expl.setPosition(v);
   explosionList.push_back(expl);
}


void ExplosionManager::draw() const{
   for(auto& ex: explosionList){
      ex.draw();
   }
}

void ExplosionManager::update(Uint32 ticks) {
   static int frames = Gamedata::getInstance().getXmlInt("Explosion/frames");
   std::list<MultiSprite>::iterator it = explosionList.begin();
   while(it != explosionList.end()){
      if(it->getTotalFrames() > frames){
         it = explosionList.erase(it);
      }else{
         it->update(ticks);
         ++it;
      }
   }
}
