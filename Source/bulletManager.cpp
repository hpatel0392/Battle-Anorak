#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bulletManager.h"


BulletManager & BulletManager::getInstance() {
   static BulletManager instance;
   return instance;
}

BulletManager::~BulletManager() {
   reset();
}

void BulletManager::reset(){
   for(auto * bl: bulletLists){
      bl->clear();
      delete bl;
      bl = nullptr;
   }
   bulletLists.clear();

   for(auto * fl: freeLists){
      fl->clear();
      delete fl;
      fl = nullptr;
   }
   freeLists.clear();
}

std::list<Bullet> * BulletManager::requestBulletList(){
   std::list<Bullet> * BL = new std::list<Bullet>();
   bulletLists.emplace_back(BL);
   return bulletLists.back();
}

std::list<Bullet> * BulletManager::requestFreeList(const std::string & name, int limit, const Drawable* o){
   std::list<Bullet> *FL = new std::list<Bullet>();
   freeLists.emplace_back(FL);
   std::list<Bullet> * fl = freeLists.back();
   std::srand(std::time(0));
   for(int i = 0; i < limit; i++){
      fl->emplace_back(name, o);
      if(name != "DestructoDisc") fl->back().setScale(std::rand()%2+1);
   }
   return fl;
}

bool BulletManager::collided(const Drawable* d){
   for(auto bl: bulletLists){
      for(auto& bullet: *bl){
         if(bullet.isOwner(d)) break;
         if(strategy->execute(bullet, *d)){ // do more here if needed
            bullet.setCollided();
            return true;
         }
      }
   }
   return false;
}
