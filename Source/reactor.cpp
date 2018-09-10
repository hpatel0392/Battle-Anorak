#include <random>
#include "reactor.h"
#include "actor.h"
#include "gamedata.h"

Reactor::Reactor(const std::string & s): 
  MultiSprite(s),
  target(nullptr)
{
   if(s == "Godzilla") return;
   std::random_device rd;
   std::mt19937 mt(rd());
   std::uniform_real_distribution<double> distX(0.0, (double)worldWidth);
   std::uniform_real_distribution<double> distY(0.0, (double)worldHeight);
   setPosition(Vector2f((int)distX(mt), (int)distY(mt))); 
}

Reactor::Reactor(const Reactor& r):
  MultiSprite(r),
  target(r.target)
{}

Reactor& Reactor::operator=(const Reactor& r){
  MultiSprite::operator=(r);
  target = r.target;
  return *this;
}

void Reactor::react(){
  if(target == nullptr) return;
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= target->getPosition()[0]+target->getScaledWidth()/2;
  float ey= target->getPosition()[1]+target->getScaledHeight()/2; 

   if ( x < ex ) goRight();
   if ( x > ex ) goLeft();
   if ( y < ey ) goDown();
   if ( y > ey ) goUp();
}

void Reactor::update(Uint32 ticks){
  MultiSprite::update(ticks);
  react();
}

void Reactor::goLeft()  { setVelocityX( -abs(getVelocityX()) );  }
void Reactor::goRight() { setVelocityX( fabs(getVelocityX()) );  }
void Reactor::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void Reactor::goDown()  { setVelocityY( fabs(getVelocityY()) );  } 


