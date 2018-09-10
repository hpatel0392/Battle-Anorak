#include "boss.h"
#include "actor.h"
#include "gamedata.h"
#include "player.h"


Boss::Boss(const std::string & name):
  Reactor(name),
  hp(Gamedata::getInstance().getXmlInt("Godzilla/health")),
  cannon1("SpiritBomb", Gamedata::getInstance().getXmlInt("BossAmmo"),  static_cast<const Drawable*>(this)),
  cannon2("SpiritBomb", Gamedata::getInstance().getXmlInt("BossAmmo"),  static_cast<const Drawable*>(this))
{}

void Boss::shoot(){
  static Vector2f correctionRight(510, 100);
  static Vector2f correctionLeft(0, 100);
  static Vector2f cannon2Left(  150, -5);
  static Vector2f cannon2Right(-150, -5);
  static int minimumSpeed = Gamedata::getInstance().getXmlInt("SpiritBomb/bulletSpeed");

   Vector2f plusOrMinus(std::rand()%2 == 0?-1:1, std::rand()%2== 0?-1:1); 
   Vector2f fuzzify(std::rand()%200, std::rand()%200);
   fuzzify[0] = fuzzify[0]*plusOrMinus[0];
   fuzzify[1] = fuzzify[1]*plusOrMinus[1];

   Vector2f tpos = target->getPosition() + fuzzify;
   Vector2f bpos = getPosition()+correctionLeft;
   Vector2f bpos2 = getPosition()+correctionRight;

   if(getVelocity()[0] < 0){
     Vector2f vel = (tpos - bpos);
     
     if( vel.magnitude() < minimumSpeed){
       vel = minimumSpeed * vel.normalize();
     }

     cannon1.shoot(bpos,  vel);
     cannon2.shoot(bpos + cannon2Left, vel );
   } else {
      Vector2f vel = (tpos - bpos2);
     
     if( vel.magnitude() < minimumSpeed){
       vel = minimumSpeed * vel.normalize();
     }

      cannon1.shoot(bpos2, vel );
      cannon2.shoot(bpos2 + cannon2Right, vel );
   }
}

void Boss::react(){
   Reactor::react();
   static int numCalls = 0;
   const Player * p = static_cast<const Player *>(target);
   if(++numCalls%5 && !(p->dead()) )
      shoot();
}

void Boss::update(Uint32 ticks){
   if(!dead()){
     MultiSprite::update(ticks);
     react();
   }

   cannon1.update(ticks);
   cannon2.update(ticks);

if(dead())setPosition(Vector2f(-500, -600));
}

void Boss::draw(){
   if(!dead())Reactor::draw();

if(cannon1.blSize() == 0 && cannon2.blSize() == 0) return;
   cannon1.draw();
   cannon2.draw();
}
