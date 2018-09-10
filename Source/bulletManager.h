#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <string>
#include <list>
#include <vector>
#include "bullet.h"
#include "collisionStrategy.h"
#include "drawable.h"

class BulletManager{
public:
   static BulletManager& getInstance();
   ~BulletManager();
   
   BulletManager(const BulletManager&) = delete;
   BulletManager& operator=(const BulletManager&) = delete;

   std::list<Bullet> * requestBulletList();
   std::list<Bullet> * requestFreeList(const std::string & , int, const Drawable*);
   bool collided(const Drawable*);   

   void reset();
   
private:
   std::vector<std::list<Bullet> *> bulletLists;
   std::vector<std::list<Bullet> *> freeLists;
   CollisionStrategy* strategy;

   BulletManager(): 
      bulletLists(),
      freeLists(),
      strategy( new PerPixelCollisionStrategy())
   {}
};
#endif
