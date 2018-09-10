#ifndef BOSS_H
#define BOSS_H

#include <string>
#include "reactor.h"
#include "gun.h"

class Boss : public Reactor {
public:
   Boss(const std::string & );
   Boss(const Boss &) = delete;
   Boss & operator=(const Boss&) = delete;

   virtual void react();
   virtual void update(Uint32);
   virtual void draw();
   bool dead(){ return hp <= 0; };
   void hit(){ hp-=5; };
   int getHP() const{ return hp; };
private:
   int hp;
   Gun cannon1;
   Gun cannon2;
  
   void shoot();

};
#endif
