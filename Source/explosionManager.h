#ifndef EXPLOSIONMANAGER_H
#define EXPLOSIONMANAGER_H

#include <string>
#include <list>
#include <cmath>
#include <vector>
#include "vector2f.h"
#include "multisprite.h"

class ExplosionManager{
public:
   static ExplosionManager& getInstance();
   ~ExplosionManager();
   
   ExplosionManager(const ExplosionManager&) = delete;
   ExplosionManager& operator=(const ExplosionManager&) = delete;

   void addExplosion (const Vector2f&);
   void draw() const;
   void update(Uint32 ticks);

   void reset();
   
private:
   std::list<MultiSprite> explosionList;

   ExplosionManager(): 
      explosionList()
   {}
};
#endif
