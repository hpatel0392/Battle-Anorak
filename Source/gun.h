#ifndef GUN_H
#define GUN_H

#include <string>
#include <list>
#include "bullet.h"
#include "bulletManager.h"
#include "vector2f.h"
#include "drawable.h"

class Gun{
public:
   explicit Gun(const std::string& name, int limit, const Drawable* o):
      bulletList(BulletManager::getInstance().requestBulletList()),
      freeList(BulletManager::getInstance().requestFreeList(name, limit, o)),
      minSpeed( Gamedata::getInstance().getXmlInt(name+"/bulletSpeed") ),
      bulletInterval(Gamedata::getInstance().getXmlInt(name+"/bulletInterval")),
      timeSinceLastFrame(0)
   { }

   void shoot(const Vector2f&, const Vector2f&);
   void update(Uint32 ticks);
   void draw() const;
   int blSize() const;
   int flSize() const;
       
 
private:
   std::list<Bullet> * bulletList;
   std::list<Bullet> * freeList;
   float minSpeed;
   float bulletInterval;
   float timeSinceLastFrame;

};
#endif
